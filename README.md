# cyrw_lock
C++的读写锁，可实现并行读时不加锁，只要进行写时才加锁

## 文件说明
1.cyrw_lock.h  读写锁头文件<br>
2.cyrw_lock.cpp 读写锁实现文件<br>
3.test_lock.cpp 读写锁的测试文件，在文件中使用了多线程进行读、写操作，测试中若读写均不使用usleep，会出现大量的读之后又大量的写，应该是靠CPU的时间片分配才可进行操作<br>
4.test_lock_DEBUG.mk 测试工程的makefile文件<br>
5.test_lock.prj 测试工程的工程文件

## 使用说明
1.创建锁对象后，需要根据实际读还是写进行区分，若读使用read_lock()和read_unlock()，写使用write_lock()和write_unlock()
2.在工程的makefile需要添加-lpthread
