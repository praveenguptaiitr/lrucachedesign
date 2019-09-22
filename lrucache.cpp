using namespace std;
#include <iostream>
#include <list>
#include <stdio.h>
#include <pthread.h>
#include "lrucachedef.h"
#include <unordered_map>
#include <sys/time.h>
#include <unistd.h>

/**
 * LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

typedef struct SingleListNode
{
	int key;
	int val;
} LNode;

class LRUCache {
	int cacheSize;
	list<LNode> l;
	unordered_map<int, list<LNode>::iterator> cachemap;
	public:
	LRUCache(int capacity) {
		cacheSize = capacity;
	}

	int get(int key) {
		cout << "LRUCache get( " << key << " )" << endl;
		int val;
		list<LNode>::iterator it;
		if(cachemap.find(key) == cachemap.end())
			return -1;
		else
		{
			it = cachemap[key];
			val = it->val;
			LNode lnode;
			lnode.key = key;
			lnode.val = val;
			l.erase(it);
			l.push_front(lnode);
			cachemap[key] = l.begin();
		}
		return val;        
	}

	void put(int key, int value) {
		cout << "LRUCache put( " << key << ", " << value << " )" << endl;
		list<LNode>::iterator it;
		if(cachemap.find(key) == cachemap.end())
		{
			if(l.size() == cacheSize)
			{
				LNode lastnode = l.back();
				l.pop_back();
				cachemap.erase(lastnode.key);
			}
		}
		else
		{
			it = cachemap[key];
			l.erase(it);
		}
		LNode listnode;
		listnode.key = key;
		listnode.val = value;
		l.push_front(listnode);
		cachemap[key] = l.begin();

		return;
	}

	void printCache()
	{
		list<LNode>::iterator it;
		cout << endl << "Current Cache Map Pairings Key --> Value:" << endl;
		for(it = l.begin(); it != l.end(); it++)
		{
			cout << it->key << " --> " << it->val << endl;
		}
		cout << endl;
		return;
	}
};


int main(int argc, char** argv)
{

	time_t start_time = time(NULL);
	struct tm* start_watch_time;
	start_watch_time = localtime(&start_time);

#ifdef _ENABLE_LOGS_INFO_TIME_
	printf("\nthread: [%ld] function: [%s] line: [%d] Program Start Time: [%02d:%02d:%02d]\n\n", pthread_self(), __func__, __LINE__,  
			start_watch_time->tm_hour, start_watch_time->tm_min, start_watch_time->tm_sec);
#endif

	if(argc != 1)
	{
#ifdef _ENABLE_LOGS_ERR_
		printf("thread: [%ld] function: [%s] line: [%d] lrucache usage: ./lrucache\n", pthread_self(), __func__, __LINE__);
#endif
		return -1;
	}
#ifdef _ENABLE_LOGS_INFO_
	printf("thread: [%ld] function: [%s] line: [%d] arguments passed: [%s]\n", pthread_self(), __func__, __LINE__, argv[0]);
#endif
	LRUCache lrucacheobj(5);
	lrucacheobj.get(1);
	lrucacheobj.put(2,1);
	lrucacheobj.put(3,5);
	lrucacheobj.put(4,10);

	lrucacheobj.printCache();

	lrucacheobj.get(3);
	lrucacheobj.get(4);
	lrucacheobj.get(10);

	lrucacheobj.printCache();

	lrucacheobj.put(4,20);
	lrucacheobj.get(4);

	lrucacheobj.printCache();

	lrucacheobj.put(10,50);
	lrucacheobj.put(1,8);

	lrucacheobj.printCache();

	lrucacheobj.get(3);
	lrucacheobj.get(2);
	lrucacheobj.get(10);
	lrucacheobj.get(1);

	lrucacheobj.printCache();

	lrucacheobj.put(20,50);
	lrucacheobj.put(100,8);

	lrucacheobj.printCache();

#ifdef _ENABLE_LOGS_INFO_
	printf("thread: [%ld] function: [%s] line: [%d] ", pthread_self(), __func__, __LINE__);

#endif
	//sleep(10);
	time_t end_time = time(NULL);
	struct tm* end_watch_time;
	end_watch_time = localtime(&end_time);

#ifdef _ENABLE_LOGS_INFO_TIME_
	printf("\n\nthread: [%ld] function: [%s] line: [%d] Work Completed in seconds: [%.5f] Program End Time: [%02d:%02d:%02d]\n", pthread_self(), __func__, __LINE__,  
			difftime(end_time, start_time), 
			end_watch_time->tm_hour, end_watch_time->tm_min, end_watch_time->tm_sec );
#endif

	return 1;
}

