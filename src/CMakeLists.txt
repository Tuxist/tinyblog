find_package(httppp REQUIRED)

set(tinyblogSrcs
  template.cpp
  blog.cpp
)

include_directories(
  ${httppp_INCLUDE_DIR}
)

add_executable (tinyblog ${tinyblogSrcs})

target_link_libraries(tinyblog ${httppp_LIBRARIES})

install(TARGETS tinyblog DESTINATION bin)
