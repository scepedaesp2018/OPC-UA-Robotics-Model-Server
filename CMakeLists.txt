cmake_minimum_required(VERSION 3.2)
project(opcua-Robotics-server)
# open62541 must be installed.
# If in custom path, then use -DCMAKE_PREFIX_PATH=/home/user/install
find_package(open62541 1.1 REQUIRED COMPONENTS FullNamespace)

# Output directory for Nodeset Compiler
set(GENERATE_OUTPUT_DIR "${CMAKE_BINARY_DIR}/src_generated/")
file(MAKE_DIRECTORY "${GENERATE_OUTPUT_DIR}")
include_directories("${GENERATE_OUTPUT_DIR}")

# Generate types and namespace for DI
set(OPEN62541_DIR /home/ubuntu18ros/open62541)

# Generate types and namespace for DI
    ua_generate_nodeset_and_datatypes(
        NAME "di"
        FILE_CSV "${OPEN62541_DIR}/deps/ua-nodeset/DI/OpcUaDiModel.csv"
        FILE_BSD "${OPEN62541_DIR}/deps/ua-nodeset/DI/Opc.Ua.Di.Types.bsd"
        NAMESPACE_MAP "2:http://opcfoundation.org/UA/DI/"
        FILE_NS "${OPEN62541_DIR}/deps/ua-nodeset/DI/Opc.Ua.Di.NodeSet2.xml"
        INTERN
    )
        
    # generate PLCopen namespace which is using DI
    ua_generate_nodeset_and_datatypes(
        NAME "Robotics"
        # PLCopen does not define custom types. Only generate the nodeset
        FILE_NS "${PROJECT_SOURCE_DIR}/Opc.Ua.Robotics.NodeSet2.xml"
        # PLCopen depends on the di nodeset, which must be generated before
        DEPENDS "di"
        INTERNAL
    )
    
    add_executable(opcua-Robotics-server
               ${UA_NODESET_DI_SOURCES}
               ${UA_NODESET_ROBOTICS_SOURCES}
               ${UA_TYPES_DI_SOURCES}
               ${UA_TYPES_ROBOTICS_SOURCES}
               main.c)
    
    add_dependencies(opcua-Robotics-server ${PROJECT_NAME}-ns-Robotics)

    
    
target_link_libraries(opcua-Robotics-server open62541::open62541)
