#include<unistd.h>
using namespace std;
int main(){
	unlink("/home/avinash/Desktop/CN/chat/mfifo");
	unlink("/home/avinash/Desktop/CN/chat/cfifo1");
	unlink("/home/avinash/Desktop/CN/chat/cfifo2");
	unlink("/home/avinash/Desktop/CN/chat/cfifo3");
	unlink("/home/avinash/Desktop/CN/chat/cfifo4");
	unlink("/home/avinash/Desktop/CN/chat/cfifo5");
}