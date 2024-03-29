test_3_20.cpp
/****************************************
*要求：
*	批量创建线程
*详解：
*	定义5个线程对象，通过将初始化构造函数
*	的返回值赋值给他们。该方法所创建线程都
*	是可连接线程，因此要用函数join来等待他
*	们结束，可以发现每次打印顺序并不一致是
*	因为CPU线程调度的随机性。
*****************************************/


test_3_21.cpp
/****************************************
*要求：
*	创建一个不传参数的线程
*详解：
*	首先定义一个线程对象，定义对象后马上
*	启动线程，然后主线程休眠1秒，这样就
* 保证了子线程能够执行完毕，然后主线程
* 退出，子线程也会退出，预防主线程过早
* 退出导致子线程没有机会执行
*****************************************/


test_3_22.cpp
/****************************************
*要求：
*	创建一个线程并传入整型参数
*详解：
*	创建线程时，把一个整型作为参数传给构造
*	函数，然后在线程函数中打印出来，并且使
*	用join()等待线程结束，函数join()会一直等
*	到子线程结束才返回并执行该函数后面的代
*	码
*****************************************/


test_3_23.cpp
/****************************************
*要求：
*	创建一个线程，并传递字符串作为参数
*详解：
*	无
*****************************************/


test_3_24.cpp
/****************************************
*要求：
*	创建一个线程，并传递结构体作为参数
*详解：
*	通过结构体传递多个值给线程函数
*****************************************/


test_3_25.cpp
/****************************************
*要求：
*	创建一个线程，传多个参数给线程函数
*详解：
*	传入多个参数给构造函数，同时线程函数也
*	要准备好同样多的形参，通过对整形地址&k
*	的引用，在线程中修改了他所指向的变量的
*	内容，所以在主线程中k的值也被修改了
*****************************************/


test_3_26.cpp
/****************************************
*要求：
*	把可连接线程转为分离线程(C++11&POSIX)
*详解：
*	我们调用detach()来分离线程，这样主线程
*	就可以不用等待子线程结束而可以自己先结
*	束。我们调用了pthead_exit(NULL)来结束
* 主线程，这样主线程就会等待子线程结束后
* 再结束。值得一提的时，他会先打印主线程
*	的k变量，是因为线程还没进行切换。
*****************************************/


test_3_27.cpp
/****************************************
*要求：
*	通过移动构造函数来启动线程
*详解：
*	通过将对象t1转换为右值引用类型后进行调
*	用，从而实现移动语义，即将t1的资源所有
*	权转移给t2，从而实现通过移动构造函数来
*	启动线程
*****************************************/


test_3_28.cpp
/****************************************
*要求：
*	线程比较
*详解：
* is_main_thread第一次调用是作为主线程
* 中的普通函数，得到的ID也与main函数的
* 主线程ID相同，第二次是子线程，则得到
* 的是子线程ID。this_thread是一个命名空间
* ，用来表示当前线程，get_id()是获取当前
* 线程的ID。
*****************************************/


test_3_29.cpp
/****************************************
*要求：
*	线程赛跑：创建10个线程，每个线程中让一
*	个变量从1累加到100万，谁先完成就打印谁
* 的ID，以此排名。为公平起见，创建线程时
*	先不让他们1占用CPU时间，直到主线程改变
* 标志位，所有线程同时开始工作。
*详解：
*	多次运行该程序，可发现每次结果都不相同
*	，线程启动时一直在while循环中通过yield
* 让出CPU时间，直到主线程改变标志位，所有
*	线程同时开始工作，这样就能保证每个线程
*****************************************/


test_3_30.cpp
/****************************************
*要求：
*	暂停线程到下一分钟
*详解：
*	主线程从sleep_until处挂起，然后到了下
*	一个整分钟（分钟+1，秒钟为0，主线程继
*	续执行
*****************************************/


test_3_31.cpp
/****************************************
*要求：
*	暂停线程5秒
*详解：
*	无
*****************************************/
