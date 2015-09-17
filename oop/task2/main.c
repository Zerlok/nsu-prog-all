#include "factory.h"


Class Student
{

}


void create_student(char *firstname, char *lastname, int age)


int main(int argc, char **argv)
{
	Student *me = new(Student, "Danil", "Troshnev", 20);

	return 0;
}
