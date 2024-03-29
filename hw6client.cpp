
// ecs36b first program

#include <iostream>
#include "ecs36b_Exception.h"

// JSON RPC part
#include "hw6client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

using namespace jsonrpc;
using namespace std;

int
main()
{
  // distributed wordle demo for 11/23/2022
  HttpClient httpclient("http://127.0.0.1:8384");
  // HttpClient httpclient("https://5f43-2601-200-c001-9ff0-d5cd-ca2a-e2c4-2fcc.ngrok.io");
  // HttpClient httpclient("https://2ada-73-66-168-157.ngrok.io");
  // HttpClient httpclient("https://fa470c1cc98f.ngrok.io");
  hw6Client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value myv;
  Json::Value jv_list;
  
  jv_list[0] = "987654323";
  jv_list[1] = "987654326";
  jv_list[2] = "987654329";

  //
  try {
    myv = myClient.set_name("set_name", jv_list, "hi5555");
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;

  try {
    // worry
    myv = myClient.obtain("obtain", "Wordle", "00000000");
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;

  string new_game_id = (myv["game_id"]).asString();
  try {
    // mound
    myv = myClient.guess("guess", "Wordle", new_game_id, "mound");
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;

  try {
    // sicky
    myv = myClient.guess("guess", "Wordle", new_game_id, "sicky");
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;

  try {
    // earth
    myv = myClient.guess("guess", "Wordle", new_game_id, "earth");
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;

  exit(-2);

  try {
   // worry
    myv = myClient.submit("submit", new_game_id, "bar");
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;

  exit(-1);
  
  jv_list[0] = "987654322";
  jv_list[1] = "987654325";
  jv_list[2] = "987654328";
  
  //
  try {
    myv = myClient.set_name("set_name", jv_list, "bar");
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;

    // obtain and new
  try {
    myv = myClient.obtain("obtain", "Wordle", "00000000");
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;

  // guess
  if ((myv["game_id"].isNull() == false) &&
      (myv["game_id"].isString() == true))
    {
      try {
	// earth
	myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
			     "earth");
      } catch (JsonRpcException &e) {
	cerr << e.what() << endl;
      }

      // exit(-1);

      try {
	// mound
	myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
			     "mound");
      } catch (JsonRpcException &e) {
	cerr << e.what() << endl;
      }

      try {
	// sicky
	myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
			     "sicky");
      } catch (JsonRpcException &e) {
	cerr << e.what() << endl;
      }

      std::cout << myv.toStyledString() << std::endl;
    }

  exit(-5);
  
  try {
    // worry
    myv = myClient.guess("guess", "Wordle", "19056_2022-11-24T20:26:16+0000",
			 "worry");
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;

  try {
    // worry
    myv = myClient.submit("submit", "19056_2022-11-24T20:26:16+0000", "foo");
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;

  // obtain and new
  try {
    myv = myClient.obtain("obtain", "Wordle", "00000000");
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;

  // guess
  if ((myv["game_id"].isNull() == false) &&
      (myv["game_id"].isString() == true))
    {
      try {
	// earth
	myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
			     "earth");
      } catch (JsonRpcException &e) {
	cerr << e.what() << endl;
      }

      // exit(-1);

      try {
	// mound
	myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
			     "mound");
      } catch (JsonRpcException &e) {
	cerr << e.what() << endl;
      }

      try {
	// sicky
	myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
			     "sicky");
      } catch (JsonRpcException &e) {
	cerr << e.what() << endl;
      }

      std::cout << myv.toStyledString() << std::endl;
    }
  return 0;
}
