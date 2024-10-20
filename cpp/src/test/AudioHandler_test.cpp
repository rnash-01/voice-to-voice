#include <test/AudioHandler.h>

TEST_F(AudioReaderTest, StartLoadDoesCreateControlThread)
{
	BinaryTree b;
	// Quick check that the control thread is, at first, NULL
	ASSERT_EQ(a->control, (std::thread*) 0);
	std::cout << "Control is, indeed, NULL" << std::endl;

	// Now try 'startLoad'
	std::cout << "Trying to startLoad" << std::endl;
	a->startLoad(b);
	std::cout << "Successful" << std::endl;
	EXPECT_NE(a->control, (std::thread*) 0);

	// Now try 'stopLoad'
	a->stopLoad();
	EXPECT_EQ(a->control, (std::thread*) 0);
}

TEST_F(AudioReaderTest, DoesBindCallBack)
{
	BinaryTree b;
	ASSERT_EQ(a->onLoad, (int (*)(BYTE*, size_t)) NULL);
	
	a->bindLoadCallback(dummyCallback);
	EXPECT_EQ(a->onLoad, &dummyCallback);
}

TEST_F(AudioReaderTest, DoesRunCallbackFromThread)
{
	BinaryTree b;
	ASSERT_EQ(a->onLoad, (int (*)(BYTE*, size_t)) NULL);

	a->bindLoadCallback(dummyCallback);
	a->startLoad(b);

	a->stopLoad();
}

	
