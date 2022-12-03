
// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>
#include <iostream>

// ecs36b
#include "ecs36b_Common.h"
#include "JvTime.h"

using namespace std;

int
main(void)
{
  Json::Value lv_log;
  lv_log["arg action"] = "check team scores";

  int rc = 0;
  int error_code = 0;
  int i,j;
  Json::Value result;
  
  char buf_fname0[256];
  bzero(buf_fname0, 256);
  snprintf(buf_fname0, 255, "./config/ecs36b_teams_array.json.000");

  char buf_fname1[256];
  bzero(buf_fname1, 256);
  snprintf(buf_fname1, 255, "./config/ecs36b_teams.json.003");

  char buf_fname2[256];
  bzero(buf_fname2, 256);
  snprintf(buf_fname2, 255, "./config/ecs36b_students.json.003");

  Json::Value lv_teams_array;
  Json::Value lv_teams;
  Json::Value lv_students;

  try {
    rc = myFile2JSON(buf_fname0, &lv_teams_array);
    if (rc != 0)
      {
	error_code = rc;
	throw ecs36b_Exception
	  { ("myFile2JSON error " + std::string { buf_fname0 }) };
      }

    if((lv_teams_array.isNull() == true) ||
       (lv_teams_array.isArray() == false))
      {
	error_code = -1;
	std::cout << lv_teams_array.toStyledString() << std::endl;
	throw ecs36b_Exception
	  { ("teams array JSON format incorrect " + std::string { buf_fname0 }) };
      }

    rc = myFile2JSON(buf_fname1, &lv_teams);
    if (rc != 0)
      {
	error_code = rc;
	throw ecs36b_Exception
	  { ("myFile2JSON error " + std::string { buf_fname1 }) };
      }

    if((lv_teams.isNull() == true) ||
       (lv_teams.isObject() == false))
      {
	error_code = -1;
	throw ecs36b_Exception
	  { ("teams JSON format incorrect " + std::string { buf_fname1 }) };
      }

    rc = myFile2JSON(buf_fname2, &lv_students);
    if (rc != 0)
      {
	error_code = rc;
	throw ecs36b_Exception
	  { ("myFile2JSON error " + std::string { buf_fname2 }) };
      }

    if ((lv_students.isNull() == true) ||
	(lv_students.isObject() == false))
      {
	error_code = -2;
	throw ecs36b_Exception
	  { ("students JSON format incorrect " + std::string { buf_fname2 }) };
      }

    for (i = 0; i < lv_teams_array.size(); i++)
    {
      if (lv_teams_array[i].isString() == false)
	{
	  error_code = -3;
	  throw ecs36b_Exception
	    { ("team name array element not string") };
	}
      
      std::string lv_team_name = (lv_teams_array[i]).asString();
      Json::Value lv_member_list = lv_teams[lv_team_name];
      
      if ((lv_member_list.isNull() == true) ||
	  (lv_member_list.isArray() == false) ||
	  (lv_member_list.size() > 4))
	  
	{
	  error_code = -4;
	  std::cout << lv_member_list.size() << std::endl;
	  std::cout << lv_member_list.toStyledString() << std::endl;
	  throw ecs36b_Exception
	    { ("team member list not array") };
	}
      
      Json::Value lv_score_list;
      for (j = 0; j < lv_member_list.size(); j++)
	{
	  std::string lv_student_id = (lv_member_list[j]).asString();
	  int lv_score = lv_students[lv_student_id]["score"].asInt();
	  lv_score_list[j] = lv_score;
	}
      result[lv_team_name] = lv_score_list;
    }
  } catch (ecs36b_Exception& e) {
    std::cerr << e.what() << std::endl;
    result["reason"] = e.what();
    result["error_code"] = error_code;
  }

  lv_log["result"] = result;
  myPrintLog(lv_log.toStyledString(), "./config/hw6server.log");
  std::cout << result.toStyledString() << std::endl;
  return 0;
}
