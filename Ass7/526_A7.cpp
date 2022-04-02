#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <stack>
#include <time.h>
#include <vector>
#include <unistd.h>
using namespace std;
mutex m;
stack < int >item1;		//stack shared by the supplier and consumer 
stack < int >item2;
stack < int >item3;
stack < int >item4;
stack < int >item5;
int items_produced[5] = { 0, 0, 0, 0, 0 };
int items_consumed[5] = { 0, 0, 0, 0, 0 };

void push_item (stack < int >*s, int no_of_items)
{

  for (int i = 0; i < no_of_items; i++)
    s->push (1);

}

int pop_item (stack < int >*s, int no_of_items)
{
  if (s->size() - no_of_items < 0)
    return -1;
  else
    {

      for (int i = 0; i < no_of_items; i++)
      s->pop ();
      return 1;
    }
}

void supplier ()
{
  srand (time (NULL));
  while (true)
    {
      m.lock ();
      if (items_produced[0] >= 200 && items_produced[1] >= 200
	  && items_produced[2] >= 200 && items_produced[3] >= 200
	  && items_produced[4] >= 200)
	{
	  m.unlock ();
	  break;
	}
      int n = rand () % 5 + 1;
      int p = rand () % 15 + 1;
      cout << "Adding item" << n << " by " << p << " units" << endl;
      if (items_produced[n - 1] == 200)
	{
	  cout << "Maximum production Capacity for item" << n << "reached" <<
	    endl;
	  m.unlock ();
	  continue;
	}
      else
	{
      items_produced[n - 1]+=p;
	  switch (n)
	    {
	    case 1:
	      push_item (&item1, p);
	      m.unlock ();
	      break;
	    case 2:
	      push_item (&item2, p);
	      m.unlock ();
	      break;
	    case 3:
	      push_item (&item3, p);
	      m.unlock ();
	      break;
	    case 4:
	      push_item (&item4, p);
	      m.unlock ();
	      break;
	    case 5:
	      push_item (&item5, p);
	      m.unlock ();
	    }
	  
	}


    }
  cout << "Maximum Supply Capacity for all items reached" << endl;
}

void consumer ()
{
    sleep(10);
  srand (time (NULL));
  while (true)
    {
      m.lock ();
      if (items_consumed[0] >= 200 && items_consumed[1] >= 200
	  && items_consumed[2] >= 200 && items_consumed[3] >= 200
	  && items_consumed[4] >= 200)
	{
	  m.unlock ();
	  break;
	}
      int temp;
      int n = rand () % 5 + 1;
      int p = rand () % 24 + 2;
      cout << "Consuming " << p << " item" << n << endl;
      items_consumed[n - 1]+=p;
      switch (n)
	{
	case 1:
	  temp = pop_item (&item1, p);
	  if (temp == -1)
	    cout << "Item Unavailable" << endl;
	  m.unlock ();
	  break;
	case 2:
	  temp = pop_item (&item2, p);
	  if (temp == -1)
	    cout << "Item Unavailable" << endl;
	  m.unlock ();
	  break;
	case 3:
	  temp = pop_item (&item3, p);
	  if (temp == -1)
	    cout << "Item Unavailable" << endl;
	  m.unlock ();
	  break;
	case 4:
	  temp = pop_item (&item4, p);
	  if (temp == -1)
	    cout << "Item Unavailable" << endl;
	  m.unlock ();
	  break;
	case 5:
	  temp = pop_item (&item5, p);
	  if (temp == -1)
	    cout << "Item Unavailable" << endl;
	  m.unlock ();
	}
      
    }
  cout << "Maximum Consumption reached " << endl;
}

int main ()
{
  thread t1 (supplier);
  thread t2 (consumer);
  t2.join ();
  t1.join ();

}
