# - Try to find Libpqxx
# Once done this will define
#  LIBPQXX_FOUND - System has Libpqxx
#  LIBPQXX_INCLUDE_DIRS - The Libpqxx include directories
#  LIBPQXX_LIBRARIES - The libraries needed to use Libpqxx
#  LIBPQXX_DEFINITIONS - Compiler switches required for using Libpqxx

find_package(PkgConfig)
pkg_check_modules(PC_LIBPQXX QUIET libpqxx)
set(LIBPQXX_DEFINITIONS ${PC_LIBPQXX_CFLAGS_OTHER})

find_path(LIBPQXX_INCLUDE_DIR pqxx/pqxx
          HINTS ${PC_LIBPQXX_INCLUDEDIR} ${PC_LIBPQXX_INCLUDE_DIRS}
         )

find_library(LIBPQXX_LIBRARY NAMES pqxx
             HINTS ${PC_LIBPQXX_LIBDIR} ${PC_LIBPQXX_LIBRARY_DIRS} )

set(LIBPQXX_LIBRARIES ${LIBPQXX_LIBRARY} )
set(LIBPQXX_INCLUDE_DIRS ${LIBPQXX_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBPQXX_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(Libpqxx  DEFAULT_MSG
                                  LIBPQXX_LIBRARY LIBPQXX_INCLUDE_DIR)

mark_as_advanced(LIBPQXX_INCLUDE_DIR LIBPQXX_LIBRARY )
