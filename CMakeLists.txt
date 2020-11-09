cmake_minimum_required(VERSION 3.2)
project(opcua-Robotics-server)
# open62541 must be installed.
# If in custom path, then use -DCMAKE_PREFIX_PATH=/home/user/install
find_package(open62541 1.1 REQUIRED COMPONENTS FullNamespace)

# Output directory for Nodeset Compiler
set(GENERATE_OUTPUT_DIR "${CMAKE_BINARY_DIR}/src_generated/")
file(MAKE_DIRECTORY "${GENERATE_OUTPUT_DIR}")
include_directories("${GENERATE_OUTPUT_DIR}")

#set(UA_NAMESPACE_ZERO FULL)

ua_generate_nodeset_and_datatypes(
        NAME "Robotics"
        TARGET_PREFIX "${PROJECT_NAME}"
        FILE_NS "${PROJECT_SOURCE_DIR}/Opc.Ua.Robotics.NodeSet2.xml"
#	FILE_CSV "${PROJECT_SOURCE_DIR}/NodeIds.csv"
#	NAMESPACE_MAP "1:http://opcfoundation.org/UA/Robotics/"
        OUTPUT_DIR "${GENERATE_OUTPUT_DIR}"
        INTERNAL
)

# Previous macro automatically sets some variables which hold the generated source code files using the provided NAME
add_executable(opcua-Robotics-server
               ${UA_NODESET_ROBOTICS_SOURCES}
               ${UA_TYPES_ROBOTICS_SOURCES}
               main.c)
               
# Make sure the nodeset compiler is execute before compiling the main file
add_dependencies(opcua-Robotics-server ${PROJECT_NAME}-ns-Robotics)

target_link_libraries(opcua-Robotics-server open62541::open62541)
