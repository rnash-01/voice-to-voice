#include <test/WAVHandler.h>

TEST_F(WAVReaderTest, DoesOpenFile)
{
	r->load();
	ASSERT_EQ(r->getNChannels(), 1);
}
