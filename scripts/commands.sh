# Command reference. Copy individual Bash examples from the repository root.
# Never execute/source the whole file. No build/GUI/network execution was
# performed for this reference; native compiler, display and runtime QA remain.
# Source is Qt 5-era: C++11, QtQuick/QtQuick.Window 2.12, VirtualKeyboard 2.4.
# Use an already installed compatible Qt 5 desktop kit (5.12+ QML imports) with
# matching C++ compiler, Qt Quick/QML, Virtual Keyboard runtime plugin and make.
# This is not a verified Qt 6 port. Exact compiler/kit versions are not pinned.
# Do not reuse someone else's QtWSServer.pro.user machine-specific settings.
# Open QtWSServer.pro in Qt Creator and select your own kit for other platforms.
# No CMake, package-manager install, test or release workflow is defined.
#
# qmake syntax/default target and CONFIG are based on official tool docs:
# https://doc.qt.io/archives/qt-5.15/qmake-variable-reference.html
# https://doc.qt.io/qt-6/qmake-running.html
# The latter documents qmake syntax only, NOT compatibility of this app with Qt 6.

# === Linux/Bash + matching Qt 5 qmake / GNU make ===
# Both repositories use QtWSServer.pro: default executable name QtWSServer.
# Use separate, new build directories; qmake/make create and overwrite artifacts.
mkdir -p build-debug
(cd build-debug && qmake ../QtWSServer.pro "CONFIG+=debug" "CONFIG-=release" && make)
# Release is an alternative build, not a runtime flag.
mkdir -p build-release
(cd build-release && qmake ../QtWSServer.pro "CONFIG+=release" "CONFIG-=debug" && make)
# qmake must resolve to the selected Qt 5 kit; do not blindly use qmake6.
# Once built and after reviewing runtime warnings below, Linux desktop launch:
./build-debug/QtWSServer
# Alternative release executable:
./build-release/QtWSServer

# === What this revision actually does ===
# Despite repository name, the .pro links only quick; no WebSockets module or
# server source exists here. Startup opens a 1024x1024 "Hello World" window and
# advances a red rectangle through a worker thread. NO server/port/bind flags.
# main forces QT_IM_MODULE=qtvirtualkeyboard; the QML plugin must be available.
# No custom argument parser or headless mode; do not assume --help is a dry run.
# QML load/component creation are not checked before rootObjects().at(0) and
# pointer dereferences. Missing QML plugins can cause startup failure/crash.
# Worker directly updates a main-thread QObject's properties without locking;
# its endless loop never emits finished and has no explicit stop path.
# Native behavior/thread shutdown is not validated by Bash/QRC static parsing.

# === Platform/deployment boundaries ===
# Windows build must use the chosen Qt kit's compiler shell and matching make
# tool (MSVC/MinGW are not interchangeable); use Qt Creator rather than guessing.
# macOS creates a bundle; these Linux executable paths are not macOS instructions.
# qmake defines a target-only install rule on non-Android Unix (/opt) and QNX
# (/tmp). This does NOT bundle Qt/QML dependencies or establish deployment.
# Optional privileged Unix install, only after explicit target review:
# (cd build-release && make install)
# No sudo, firewall, packaging, or production deployment operation is implied.
