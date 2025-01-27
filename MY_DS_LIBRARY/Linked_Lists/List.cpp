#include "List.hpp"
//#include <list>

//tip: avoid using std namespace as it might invoke similar functions in standard library
using std::string;
using std::cout;
using std::cin;

/* Doubly Linked List Operations: */
void test_case_1(){
#if __cplusplus >= 201103L
	//List<int> -> without GC, standard minimal version
	List_O<int> obj({1,2,3,4,5,6,7,8,9}), //{1,2,2,4,3,3,3,7} =>duplicate set, {3,2,4,1,8,3,6} =>unsorted set
				obj2({99,88,77,66,55});
#else
	List_O<int> obj, obj2;
	for(int i=1;i<=9;++i)
		obj.push_back(i);
	for(int i=99;i>=55;i-=11)
		obj2.push_back(i);
#endif
	
	obj.traverse();//ascending order
//	for(auto& it:obj)//also works in range loops
//		cout<<it<<' ';
//	for(auto it=obj.begin();it!=obj.end();++it)// auto = List<int>::iterator
//		cout<<*it<<' ';
//	cout<<'\n';
	
	obj.traverse(true);//descending order
//	for(auto& it:obj.r_iterator_adapter())//also works in range loops
//		cout<<it<<' ';
//	for(auto it=obj.rbegin();it!=obj.rend();++it)// auto = List<int>::r_iterator
//		cout<<*it<<' ';
//	cout<<'\n';
	
	cout<<"\nBEFORE:-\n"
		<<"obj1: "<<obj<<" (front: "<<obj.front()
					   <<", tail: "<<obj.back()
					   <<", size: "<<obj.size()<<")\n"
		<<"obj2: "<<obj2<<" (front: "<<obj2.front()
		                <<", tail: "<<obj2.back()
						<<", size: "<<obj2.size()<<')';
	
	obj.merge(obj2, 2);
	
//	obj.unique();//first initialize list with duplicate set of values
	
//	obj.reverse();
	
//	obj.sort();//first initialize list with unsorted set of values
	
//	obj.sorted_insert(404);//works on sorted data (ascending/descending both orders)
	
//	obj.resize(4);//usage 1: removes nodes from last upto 'n' size
//	obj.resize(12, 100);//usage 2: appends nodes at last upto 'n' size
	
//	swap(obj, obj2);//uses move ctors & assignment operators in C++11
	
//	obj.swap_data(2, 5);
//	obj.swap_nodes(2, 5);
	
//	obj.clear();
	
//	obj.erase(5);
	
//	obj.insert(4, 404);
	
//	obj.push_middle(404);
//	obj.push_middle(new List<int>::node(404));//node transfer version
	
//	obj.pop_middle();
//	obj2.push_middle(obj.pop_middle(true));//node transfer version
	
//	for(int i=1;i<=3;++i)
//		obj.push_back(i);
	
//	for(int i=1;i<=3;++i)
//		obj.push_front(i);
	
//	for(int i=0;i<3;++i)
//		obj.pop_front();//use one at a time
//		obj2.push_front(obj.pop_front(true));
	
//	for(int i=0;i<3;++i)
//		obj.pop_back();
//		obj2.push_back(obj.pop_back(true));
	
	cout<<"\nAFTER:-\n"
		<<"obj1: "<<obj<<" (front: "<<(obj.front_node()?obj.front():0)//for exception safety during test
					   <<", tail: "<<(obj.back_node()?obj.back():0)
					   <<", size: "<<obj.size()<<")\n"
		<<"obj1 (desc): ";
	obj.traverse(true);
	cout<<"obj2: "<<obj2<<" (front: "<<(obj2.front_node()?obj2.front():0)
						<<", tail: "<<(obj2.back_node()?obj2.back():0)
						<<", size: "<<obj2.size()<<")\n"
		<<"obj2 (desc): ";
	obj2.traverse(true);
	
//	List_O<int>::clear_gc();//releasing all nodes of int type
//	List_O<int>::release_gc(10);//releasing 10 nodes of int type
}

void test_case_2(){
#if __cplusplus >= 201103L
	List<char> s1({'2','0','1','6'}), s2({'2','0','2','0'});
#else
	List<char> s1, s2;
	s1.push_back('2'); s2.push_back('2');
	s1.push_back('0'); s2.push_back('0');
	s1.push_back('1'); s2.push_back('2');
	s1.push_back('6'); s2.push_back('0');
#endif
	
	cout<<"Equals to: "<<std::boolalpha<<(s1==s2)<<'\n'
		<<"Not equals to: "<<(s1!=s2)<<'\n'
		<<"Greater than: "<<(s1>s2)<<'\n'
		<<"Less than: "<<(s1<s2)<<'\n'
		<<"Greater than & equals to: "<<(s1>=s2)<<'\n'
		<<"Less than & equals to: "<<(s1<=s2)<<'\n';
}

#if __cplusplus >= 201103L
template<typename T>
using L=List_O<T>;//renaming it, for easily changing list version

void test_case_3(){
	cout<<"BEFORE:-\n";
	L<L<int>> obj({L<int>({1,2,3,4,5}),
				   L<int>({6,7,8,9,10})}),
			  obj2;//empty list 2
//			  obj2=obj;//deep copy
//			  obj2=std::move(obj);//shallow copy, empties list 1
//			  obj2(4);//default constructs 4 emtpy lists
	
	obj.push_back(L<int>({11,12,13,14,15}));
	obj.push_front(L<int>({-5,-4,-3,-2,-1}));
	
	for(auto& _it:obj){
		for(auto& it:_it)
			cout<<it<<' ';
		cout<<'\n';
	}
	cout<<"---------------\n";
	for(auto& _it:obj.r_iterator_adapter()){
		for(auto& it:_it.r_iterator_adapter())
			cout<<it<<' ';
		cout<<'\n';
	}
	
	cout<<"\nAFTER:-\n";
	obj2=obj;//deep copy
//	obj2=std::move(obj);//shallow copy
//	swap(obj, obj2);//shallow copy
	
	for(auto& it:obj)
		it.traverse();
	cout<<"---------------\n";
	for(auto& it:obj.r_iterator_adapter())
		it.traverse(true);
}

class Fun{//for testing
	char c;
	int i;
	string s;//heap object
public:
	Fun(char c='\0',int i=0, string&& s="")noexcept:
		c(c), i(i), s(std::move(s)){}
	
	friend std::ostream& operator<<(std::ostream& out, const Fun& obj){
		out<<obj.c<<", "<<obj.i<<", "<<obj.s<<'\n';
		return out;
	}
};

void test_case_4(){
	cout<<"\nConstrutor Test (l1-> l2):-\n";
	List<string> l1({"aaa","bbb","ccc","ddd","eee","fff","ggg"}),//initializer_list ctor call
//				 l2;//default construction
//				 l2(6, "nil");//fill ctor call
//				 l2=l1;//copy construction
				 l2=std::move(l1);//move construction
	
	cout<<"l1: "<<l1<<'('<<l1.size()<<")\n"
		<<"l2: "<<l2<<'('<<l2.size()<<")\n";
	
	cout<<"\nAssignment operator Test (l1-> l2):-\n";
//	l1=l2;//l-value copy assignment
//	l1=List_O<string>(1, "new");//r-value move assignment
	l1=std::move(l2);//l-value move assignment
	
	cout<<"l1: "<<l1<<'('<<l1.size()<<")\n"
		<<"l2: "<<l2<<'('<<l2.size()<<")\n";
	
	cout<<"\nlist of 'Fun' type objects):-\n";
	Fun obj1, obj2('1', 2, "3");
	
	List<Fun> obj_list;
	
	obj_list.push_front(obj1);
	obj_list.push_back(std::move(obj2));
	obj_list.push_back('2', 3, "4");//direct initialization
	obj_list.push_back('3', 4);
	obj_list.push_back(Fun('4', 5, "6"));//moving temporary obj
	obj_list.insert(1, '$', 40404, "\"random-insert at pos 2\"");
	obj_list.erase(3);
	
	cout<<obj_list;//ascending order
}
#endif

void test_case_5(){//Efficient C.R.U.D Operations on Doubly List Double-ended Queue
	List<int> deque;
	short choice=9; int value=0;
	while(true){
		cout<<"\nSELECT YOUR CHOICE:-"
			<<"\n 1. Insert value (at front)"
			<<"\n 2. Insert value (at back)"
			<<"\n 3. Update value (at front)"
			<<"\n 4. Update value (at back)"
			<<"\n 5. Delete value (at front)"
			<<"\n 6. Delete value (at back)"
			<<"\n 7. Peek value (at front)"
			<<"\n 8. Peek value (at back)"
			<<"\n 9. View List (ascending order)"
			<<"\n10. View List (descending order)"
			<<"\n11. Exit\n==> ";
		cin>>choice;
		fflush(stdin);
		cin.clear();
		system("cls");
		try{
			switch (choice){
				case 1:
					cout<<"Enter value: ";
					cin>>value;
					deque.push_front(value);//enqueue-front
					break;
				case 2:
					cout<<"Enter value: ";
					cin>>value;
					deque.push_back(value);//enqueue-back
					break;
				case 3:
					if(deque.empty()) throw false;
					cout<<"Enter value: ";
					cin>>deque.front();
					break;
				case 4:
					if(deque.empty()) throw false;
					cout<<"Enter value: ";
					cin>>deque.back();
					break;
				case 5:
					deque.pop_front();//dequeue-front
					break;
				case 6:
					deque.pop_back();//dequeue-back
					break;
				case 7:
					if(deque.empty()) throw false;
					cout<<"Front: "<<deque.front()<<'\n';
					break;
				case 8:
					if(deque.empty()) throw false;
					cout<<"Back: "<<deque.back()<<'\n';
					break;
				case 9:
					deque.traverse();
					break;
				case 10:
					deque.traverse(true);
					break;
				case 11:
					return;
			}
		}
		catch(bool){ cout<<"List is empty!\n"; }
	}
}


int main(){
	test_case_1();//testing all operations with/without Garbage Collector Version
//	test_case_2();//use of comparison operators
//	test_case_3();//nested 2D List testing alongwith ctors & assignment operators [C++11]
//	test_case_4();//testing objects & their specific operations in list [C++11]
//	test_case_5();//using List as double-ended queue (best-case, standard version)
	
	return 0;
}
