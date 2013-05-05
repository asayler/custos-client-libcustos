/* custos_client_util.c
 * 
 * custos_client utility tool
 *
 * By Andy Sayler (www.andysayler.com)
 * Created  05/02/13
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "custos_client.h"

int main(int argc, char* argv[]) {

    (void) argc;

    int ret;
    uuid_t uuid;
    custosKeyReq_t* req;
    custosKeyRes_t* res;

    /* Create a new request */
    uuid_generate(uuid);
    req = custos_createKeyReq(uuid, "http://test.com");
    if(!req) {
	fprintf(stderr, "ERROR %s: custos_createKeyReq failed\n", argv[0]);
	return EXIT_FAILURE;
    }

    /* Get Key - 1st Attempt - Fails with CUSATTRSTAT_REQ on CUS_ATTRID_PSK */
    res = custos_getKeyRes(req);
    if(!res) {
	fprintf(stderr, "ERROR %s: custos_getKeyRes failed\n", argv[0]);
	return EXIT_FAILURE;
    }

    /* Print Response */
    fprintf(stdout, "res->resStat = %d\n", res->resStat);
    if(res->key) {
	fprintf(stdout, "res->key = %s\n", res->key);
    }
    else {
	fprintf(stdout, "res->key = NULL\n");
    }
    fprintf(stdout, "res->size = %zd\n", res->size);
    fprintf(stdout, "res->attrStat[CUS_ATTRID_PSK] = %d\n", res->attrStat[CUS_ATTRID_PSK]);

    /* Free Response */
    ret = custos_destroyKeyRes(&res);
    if(ret < 0) {
	fprintf(stderr, "ERROR %s: custos_destroyKeyRes failed\n", argv[0]);
	return EXIT_FAILURE;
    }
    if(res) {
	fprintf(stderr, "ERROR %s: custos_destroyKeyRes failed to set res to NULL\n", argv[0]);
	return EXIT_FAILURE;
    }
    
    /* Update Request */
    ret = custos_updateKeyReq(req, CUS_ATTRID_PSK, CUS_TEST_BADPSK, (strlen(CUS_TEST_BADPSK) + 1));
    if(ret < 0) {
    	fprintf(stderr, "ERROR %s: custos_updateKeyReq failed\n", argv[0]);
    	return EXIT_FAILURE;
    }

    /* Get Key - 2nd Attempt - Fails with CUSATTRSTAT_BAD on CUS_ATTRID_PSK */
    res = custos_getKeyRes(req);
    if(!res) {
	fprintf(stderr, "ERROR %s: custos_getKeyRes failed\n", argv[0]);
	return EXIT_FAILURE;
    }

    /* Print Response */
    fprintf(stdout, "res->resStat = %d\n", res->resStat);
    if(res->key) {
	fprintf(stdout, "res->key = %s\n", res->key);
    }
    else {
	fprintf(stdout, "res->key = NULL\n");
    }
    fprintf(stdout, "res->size = %zd\n", res->size);
    fprintf(stdout, "res->attrStat[CUS_ATTRID_PSK] = %d\n", res->attrStat[CUS_ATTRID_PSK]);
    
    /* Free Response */
    ret = custos_destroyKeyRes(&res);
    if(ret < 0) {
	fprintf(stderr, "ERROR %s: custos_destroyKeyRes failed\n", argv[0]);
	return EXIT_FAILURE;
    }
    if(res) {
	fprintf(stderr, "ERROR %s: custos_destroyKeyRes failed to set res to NULL\n", argv[0]);
	return EXIT_FAILURE;
    }
    
    /* Update Request */
    ret = custos_updateKeyReq(req, CUS_ATTRID_PSK, CUS_TEST_PSK, (strlen(CUS_TEST_PSK) + 1));
    if(ret < 0) {
    	fprintf(stderr, "ERROR %s: custos_updateKeyReq failed\n", argv[0]);
    	return EXIT_FAILURE;
    }
    
    /* Get Key - 3rd Attempt - Succeeds */
    res = custos_getKeyRes(req);
    if(!res) {
	fprintf(stderr, "ERROR %s: custos_getKeyRes failed\n", argv[0]);
	return EXIT_FAILURE;
    }

    /* Print Response */
    fprintf(stdout, "res->resStat = %d\n", res->resStat);
    if(res->key) {
	fprintf(stdout, "res->key = %s\n", res->key);
    }
    else {
	fprintf(stdout, "res->key = NULL\n");
    }
    fprintf(stdout, "res->size = %zd\n", res->size);
    fprintf(stdout, "res->attrStat[CUS_ATTRID_PSK] = %d\n", res->attrStat[CUS_ATTRID_PSK]);

    /* Free Response */
    ret = custos_destroyKeyRes(&res);
    if(ret < 0) {
	fprintf(stderr, "ERROR %s: custos_destroyKeyRes failed\n", argv[0]);
	return EXIT_FAILURE;
    }
    if(res) {
	fprintf(stderr, "ERROR %s: custos_destroyKeyRes failed to set res to NULL\n", argv[0]);
	return EXIT_FAILURE;
    }    

    /* Free Request */
    ret = custos_destroyKeyReq(&req);
    if(ret < 0) {
	fprintf(stderr, "ERROR %s: custos_destroyKeyReq failed\n", argv[0]);
	return EXIT_FAILURE;
    }
    if(req) {
	fprintf(stderr, "ERROR %s: custos_destroyKeyReq failed to set req to NULL\n", argv[0]);
	return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}
