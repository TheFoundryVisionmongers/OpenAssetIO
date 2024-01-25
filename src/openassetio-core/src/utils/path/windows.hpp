// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 The Foundry Visionmongers Ltd
#pragma once
#include <string_view>

#include <openassetio/export.h>

#include "./common.hpp"
#include "./windows/detail.hpp"
#include "./windows/pathTypes.hpp"

namespace openassetio {
inline namespace OPENASSETIO_CORE_ABI_VERSION {
/**
 * Utilities for Windows-specific URLs and paths.
 */
namespace utils::path::windows {
/**
 * Windows path<->URL handler.
 *
 * This is the Windows-specific entry point for converting any type of
 * Window path to/from a URL.
 */
struct FileUrlPathConverter {
  detail::WindowsUrl& urlHandler;
  detail::DriveLetter& driveLetterHandler;
  detail::UncHost& uncHostHandler;
  ForwardSlashSeparatedString& forwardSlashSeparatedStringHandler;

  pathTypes::DrivePath& drivePathHandler;
  pathTypes::UncSharePath& uncSharePathHandler;
  pathTypes::UncUnnormalisedDeviceDrivePath& uncUnnormalisedDeviceDrivePathHandler;
  pathTypes::UncUnnormalisedDeviceSharePath& uncUnnormalisedDeviceSharePathHandler;

  /**
   * Convert a Windows path into a file URL.
   *
   * Conversion is attempted starting at most specific path prefix
   * (device share paths, i.e. `\\?\UNC\`) down to least specific (drive
   * paths, i.e. `C:\`).
   *
   * @param windowsPath Path to convert.
   * @return URL string.
   * @throws InputValidationException if path is invalid or unsupported.
   */
  [[nodiscard]] Str pathToUrl(const std::string_view& windowsPath) const;

  /**
   * Convert a file URL to a Windows path.
   *
   * If the URL has a hostname it is converted to a standard UNC share
   * path. Otherwise it is assumed to be a drive path.
   *
   * No attempt is made to convert (back) to a device path, e.g. to
   * overcome the Windows MAX_PATH (260 char) limit. or to support
   * unnormalised paths.
   *
   * @param url Url to convert to a path.
   * @return `\`-separated Windows path.
   * @throws InputValidationException if URL is invalid or decodes to an
   * invalid path.
   */
  [[nodiscard]] Str pathFromUrl(const std::string_view& url) const;
};
}  // namespace utils::path::windows
}  // namespace OPENASSETIO_CORE_ABI_VERSION
}  // namespace openassetio
