#ifndef _MAZESOLVER_H
#define _MAZESOLVER_H

#include "interfaces.h"
#include "Maze.h"
#include "HashSet.h"
#include "DynArray.h"

struct MazeSolver : IMazeSolver{
private:
	struct PrvekSeznamu {
	private:
		Point data;
		PrvekSeznamu *predchoziPrvek;
	public:
		PrvekSeznamu(Point data, PrvekSeznamu *predchoziPrvek);
		~PrvekSeznamu() {};
		PrvekSeznamu* getPredchozi();
		Point getData();
	};
	
	PrvekSeznamu* frontaPrvkuCesty;
	Maze* bludiste;
	HashSet<Point, Point::Hash, Point::Equal>* hashPrvkuSeznamuCesty;
	
public:
	MazeSolver(Maze* m);
	~MazeSolver();

	virtual bool solve() override;
	virtual void saveMazeAndSolution(std::string filename) const override;
	virtual IDynArray<Point>* getPossibleMoves(Point pt) const override;
	virtual IDynArray<Point>* dropMovesInAllPaths(IDynArray<Point>* moves) const override;
	virtual bool isInCurrentHistory(Point pt) const override;
	virtual bool isInAllHistory(Point pt) const override;
	virtual void saveState(Point pt) override;
	virtual IMaze * getMaze() const override;

	// Zobrazí stav do konzole
	void show();
};

#endif // !_MAZESOLVER_H