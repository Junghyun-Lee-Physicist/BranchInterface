
# === env_setup.sh ===
#!/bin/bash
# Usage:   source env_setup.sh [static|shared]
#
# Sets up include and library paths so that you do NOT need to pass -I or -L
# when compiling or linking against BranchInterface.

# Determine this script's directory even when sourced via a relative path
##SCRIPT_DIR=$(dirname "$(realpath "$0")")
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
MODE=${1:-static}

# 1) Always add our include/ into the C++ include search path
export CPLUS_INCLUDE_PATH="${SCRIPT_DIR}/include:${CPLUS_INCLUDE_PATH}"
echo "CPLUS_INCLUDE_PATH set to: $CPLUS_INCLUDE_PATH"

# 2) Depending on mode, adjust the library search path
case "$MODE" in
  static)
    # For static linking
    export LIBRARY_PATH="${SCRIPT_DIR}/lib:$LIBRARY_PATH"
    echo "LIBRARY_PATH (static) set to: $LIBRARY_PATH"
    ;;

  shared)
    # For dynamic linking
    export LD_LIBRARY_PATH="${SCRIPT_DIR}/lib:$LD_LIBRARY_PATH"
    echo "LD_LIBRARY_PATH (shared) set to: $LD_LIBRARY_PATH"
    ;;

  *)
    echo "Usage: source env_setup.sh [static|shared]"
    return 1
    ;;
esac


