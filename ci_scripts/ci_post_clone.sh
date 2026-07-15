#!/bin/sh

# Xcode Cloud runs this right after cloning the repo, before resolving
# dependencies. This project's Xcode project is generated from project.yml by
# XcodeGen, so regenerate it in the cloud to guarantee the build matches the
# source. We also stamp the build number here so App Store Connect always gets
# a value higher than the last upload.

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

# Xcode Cloud provides CI_BUILD_NUMBER, which increases with every build.
# Builds 1-5 were already uploaded manually, so offset past them (+5) to stay
# monotonically higher than what App Store Connect has seen. All three targets
# (app, extension, framework) share CURRENT_PROJECT_VERSION, so one edit covers
# them and keeps the app/extension versions matched.
if [ -n "$CI_BUILD_NUMBER" ]; then
    BUILD_NUMBER=$((CI_BUILD_NUMBER + 5))
    echo "ci_post_clone: setting build number to $BUILD_NUMBER (CI_BUILD_NUMBER=$CI_BUILD_NUMBER)"
    sed -i '' "s/CURRENT_PROJECT_VERSION: \".*\"/CURRENT_PROJECT_VERSION: \"$BUILD_NUMBER\"/" project.yml
fi

echo "ci_post_clone: generating Xcode project from project.yml"
xcodegen generate

echo "ci_post_clone: done"
