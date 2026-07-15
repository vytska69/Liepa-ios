#!/bin/sh

# Xcode Cloud runs this right after cloning the repo, before resolving
# dependencies. This project's Xcode project is generated from project.yml by
# XcodeGen, so regenerate it in the cloud to guarantee the build matches the
# source (the committed .xcodeproj is kept in sync, this is a safety net).

set -e

echo "ci_post_clone: installing XcodeGen"
# Xcode Cloud provides Homebrew. Install XcodeGen if it isn't already present.
if ! command -v xcodegen >/dev/null 2>&1; then
    export HOMEBREW_NO_INSTALL_CLEANUP=1
    export HOMEBREW_NO_AUTO_UPDATE=1
    brew install xcodegen
fi

# CI clones into ci_scripts/..; the project root is one level up.
cd "$CI_PRIMARY_REPOSITORY_PATH"

echo "ci_post_clone: generating Xcode project from project.yml"
xcodegen generate

echo "ci_post_clone: done"
