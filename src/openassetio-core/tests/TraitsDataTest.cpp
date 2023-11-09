// SPDX-License-Identifier: Apache-2.0
// Copyright 2022 The Foundry Visionmongers Ltd
#include <type_traits>

#include <catch2/catch.hpp>

#include <openassetio/errors/exceptions.hpp>
#include <openassetio/trait/TraitsData.hpp>
#include <openassetio/trait/collection.hpp>
#include <openassetio/trait/property.hpp>

using openassetio::Int;
using openassetio::trait::TraitsData;
using openassetio::trait::TraitsDataPtr;
using openassetio::trait::property::Key;
using openassetio::trait::property::Value;

SCENARIO("TraitsData constructor is private") {
  STATIC_REQUIRE_FALSE(std::is_constructible_v<TraitsData>);
}

SCENARIO("TraitsData trait set constructor is private") {
  STATIC_REQUIRE_FALSE(std::is_constructible_v<TraitsData, const openassetio::trait::TraitSet&>);
}

SCENARIO("TraitsData copy constructor is private") {
  STATIC_REQUIRE_FALSE(std::is_constructible_v<TraitsData, const TraitsData&>);
}

SCENARIO("TraitsData make from other creates a deep copy") {
  GIVEN("an instance with existing data") {
    const TraitsDataPtr data = TraitsData::make();
    data->setTraitProperty("a", "a", Int{1});
    WHEN("a copy is made using the make copy constructor") {
      const TraitsDataPtr copy = TraitsData::make(data);
      WHEN("existing values are queried") {
        THEN("property data has been copied") {
          Value someValue;
          Int value;
          REQUIRE(copy->getTraitProperty(&someValue, "a", "a"));
          value = *std::get_if<Int>(&someValue);
          CHECK(value == Int{1});
        }
      }
      AND_WHEN("the data is modified") {
        data->setTraitProperty("a", "a", Int{3});
        THEN("the copy is unchanged") {
          Value someValue;
          Int value;
          REQUIRE(copy->getTraitProperty(&someValue, "a", "a"));
          value = *std::get_if<Int>(&someValue);
          CHECK(value == Int{1});
        }
      }
    }
  }
  GIVEN("a null TraitsDataPtr") {
    const TraitsDataPtr nullTraitsData{};

    THEN("attempting to make a copy results in an InputValidationException") {
      namespace errors = openassetio::errors;
      CHECK_THROWS_MATCHES(TraitsData::make(nullTraitsData), errors::InputValidationException,
                           Catch::Message("Cannot copy-construct from a null TraitsData"));
    }
  }
}
