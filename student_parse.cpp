
#include "ecs36b_Common.h"

using namespace std;

int
main(int argc, char *argv[])
{
  Json::Value jv_students;
  
  if (argc != 4) return -1;
  int rc = myFile2JSON(argv[1], &jv_students);
  if (rc != 0)
    {
      fprintf(stderr, "myFile2JSON error %d \n", rc);
      exit(-1);
    }
  
  FILE *in_f = fopen(argv[2], "r");
  FILE *out_f = fopen(argv[3], "w");
  if (in_f == NULL) return -2;
  if (out_f == NULL) return -2;

  char line_buf[8192];
  bzero(line_buf, 8192);

  while((rc = fscanf(in_f, "%[^\n]", line_buf)) != EOF)
    {
      // fprintf(stdout, "%s\n", line_buf);
      
      // extract fields
      char name[256];
      char temp_buf[256];
      char stud_id[256];
      char user_id[256];
      bzero(name, 256);
      bzero(temp_buf, 256);
      bzero(stud_id, 256);
      bzero(user_id, 256);

      sscanf(line_buf, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]",
	     name, temp_buf, stud_id, user_id);

      if (jv_students[stud_id].isNull() == true)
	{
	  Json::Value jv_object;
	  name[strlen(name)-1] = '\0';
	  char *nplus_ptr = &(name[1]);
	  jv_object["name"] = nplus_ptr;
	  jv_object["user id"] = user_id;
	  jv_object["team name"] = "unassigned";
	  jv_object["score"] = 0;
	  jv_students[stud_id] = jv_object;
	}
      else
	{
	  fprintf(stdout, "duplicated entry -- %16s %16s %16s\n",
		  name, stud_id, user_id);
	  exit(-1);
	}
      // get ready for next line
      fgetc(in_f);
      bzero(line_buf, 8192);
    }
  rc = myJSON2File(argv[1], &jv_students);
  
  // std::cout << jv_students.toStyledString() << std::endl;
  fclose(in_f);
  fclose(out_f);
  return 0;
}
