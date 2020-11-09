#include <open62541/plugin/log_stdout.h>
#include <open62541/server.h>
#include <open62541/server_config_default.h>
/* Files namespace_foo_flt_generated.h and namespace_foo_flt_generated.c are created from FooFlt.NodeSet2.xml in the
 * /src_generated directory by CMake */
//#include "foo_flt_nodeids.h"
//#include "namespace_Robotics_generated.h"
#include <signal.h>
#include <stdlib.h>
UA_Boolean running = true;
static void stopHandler(int sign) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
    running = false;
}
int main(int argc, char** argv) {
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);
    
    UA_Server *server = UA_Server_new();
    UA_ServerConfig_setDefault(UA_Server_getConfig(server));
    UA_StatusCode retval;
    /* create nodes from nodeset */
    if(namespace_Robotics(server) != UA_STATUSCODE_GOOD) {
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Could not add the Foo FLT nodeset. "
        "Check previous output for any error.");
        retval = UA_STATUSCODE_BADUNEXPECTEDERROR;
    } else {
        /*//Do some additional stuff with the nodes
        this will just get the namespace index, since it is already added to the server
        UA_UInt16 nsIdx = UA_Server_addNamespace(server, "http://opcfoundation.org/UA/Robotics/");
        UA_NodeId testInstanceId = UA_NODEID_NUMERIC(nsIdx, UA_FOO_FLTID_APE);
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "The Ape has ns=%d;id=%d",
                    testInstanceId.namespaceIndex, testInstanceId.identifier.numeric);*/
        retval = UA_Server_run(server, &running);
    }
    UA_Server_delete(server);
    return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}
