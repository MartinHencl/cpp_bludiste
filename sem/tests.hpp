///////////////////////////////////////////////
// Testy - tento soubor nemenit
///////////////////////////////////////////////

#ifdef COMPILE_TESTS
#ifdef TEST_POINT
TEST_CASE("Test point", "[Point]") {
	Point pta{ 0, 0 };
	Point ptb{ 1, 1 };
	Point ptc{ 1, 1 };

	REQUIRE(pta.x == 0);
	REQUIRE(pta.y == 0);
	REQUIRE(ptb.x == 1);
	REQUIRE(ptb.y == 1);

	REQUIRE(Point::Equal(pta, pta));
	REQUIRE(!Point::Equal(pta, ptb));
	REQUIRE(Point::Equal(ptb, ptb));
	REQUIRE(Point::Equal(ptb, ptc));

	REQUIRE(Point::Hash(pta) == 0);
	REQUIRE(Point::Hash(ptb) == 12);
	REQUIRE(Point::Hash(ptc) == 12);
}
#endif

#ifdef TEST_HASHSET
int __hfi(const int& i) {
	return i;
}

bool __efi(const int& i, const int& j) {
	return i == j;
}

TEST_CASE("Test IHashSet", "[IHashSet]") {
	HashSet<int, __hfi, __efi> hs{3};
	
	REQUIRE_FALSE(hs.isPresent(10));
	REQUIRE_FALSE(hs.isPresent(1));
	REQUIRE_FALSE(hs.isPresent(0));

	hs.add(10);

	REQUIRE(hs.isPresent(10));
	REQUIRE_FALSE(hs.isPresent(1));
	REQUIRE_FALSE(hs.isPresent(0));

	hs.add(10);

	REQUIRE(hs.isPresent(10));
	REQUIRE(!hs.isPresent(1));
	REQUIRE(!hs.isPresent(0));

	hs.add(11);

	REQUIRE(hs.isPresent(10));
	REQUIRE(hs.isPresent(11));
	REQUIRE(!hs.isPresent(9));
	REQUIRE(!hs.isPresent(12));

	hs.add(12);

	REQUIRE(hs.isPresent(10));
	REQUIRE(hs.isPresent(11));
	REQUIRE(hs.isPresent(12));
	REQUIRE(!hs.isPresent(9));

	hs.add(9);

	REQUIRE(hs.isPresent(10));
	REQUIRE(hs.isPresent(11));
	REQUIRE(hs.isPresent(12));
	REQUIRE(hs.isPresent(9));
}

#ifdef WIN32
TEST_CASE("Test pameti IHashSet", "[MemLeak]") {

	_CrtMemState stateBefore, stateAfter, stateDiff;

	_CrtMemCheckpoint(&stateBefore);
	{
		HashSet<int, __hfi, __efi> hs{ 10 };
		for (int i = 0; i < 1000; i++) {
			hs.add(i);
		}
	}
	_CrtMemCheckpoint(&stateAfter);

	_CrtMemDifference(&stateDiff, &stateBefore, &stateAfter);
	REQUIRE(stateDiff.lCounts[_NORMAL_BLOCK] == 0);
}
#endif
#endif

#ifdef TEST_DYNARRAY
TEST_CASE("Test IDynArray", "[IDynArray]") {
	DynArray<int> da{};

	REQUIRE(da.count() == 0);

	da.add(1);

	REQUIRE(da.count() == 1);
	REQUIRE(da.get(0) == 1);
	
	da.add(2);

	REQUIRE(da.count() == 2);
	REQUIRE(da.get(0) == 1);
	REQUIRE(da.get(1) == 2);

	REQUIRE_THROWS(da.get(3));
}

#ifdef WIN32
TEST_CASE("Test pameti IDynArray", "[MemLeak]") {

	_CrtMemState stateBefore, stateAfter, stateDiff;

	_CrtMemCheckpoint(&stateBefore);
	{
		DynArray<int> da{};
		for (int i = 0; i < 1000; i++) {
			da.add(i);
		}
	}
	_CrtMemCheckpoint(&stateAfter);
	
	_CrtMemDifference(&stateDiff, &stateBefore, &stateAfter);
	REQUIRE(stateDiff.lCounts[_NORMAL_BLOCK] == 0);
}
#endif
#endif


#else
#undef RUN_TESTS
#endif
