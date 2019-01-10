#include "MazeSolver.h"

MazeSolver::PrvekSeznamu::PrvekSeznamu(Point data, PrvekSeznamu * predchoziPrvek)
{
	this->data = data;
	this->predchoziPrvek = predchoziPrvek;
}

MazeSolver::PrvekSeznamu* MazeSolver::PrvekSeznamu::getPredchozi()
{
	return this->predchoziPrvek;
}

Point MazeSolver::PrvekSeznamu::getData()
{
	return this->data;
}

MazeSolver::MazeSolver(Maze * m)
{
	this->bludiste = m;
	this->hashPrvkuSeznamuCesty = new HashSet<Point, Point::Hash, Point::Equal>(10);
	this->frontaPrvkuCesty = nullptr;
}

MazeSolver::~MazeSolver()
{
	PrvekSeznamu* prvekMazani = frontaPrvkuCesty;
	while (prvekMazani != nullptr) {
		PrvekSeznamu* tempPrvek = prvekMazani->getPredchozi();
		delete prvekMazani;
		prvekMazani = tempPrvek;
	}
	bludiste->~Maze();
	hashPrvkuSeznamuCesty->~HashSet();
}

bool MazeSolver::solve()
{
	IDynArray<Point>* moznostiCesty = new DynArray<Point>{};
	int pocetKrokuVListu = 0;
	saveState(bludiste->getStart());									// start je dobry zacatek
	moznostiCesty = getPossibleMoves(frontaPrvkuCesty->getData());		// start do trasy
	hashPrvkuSeznamuCesty->add(frontaPrvkuCesty->getData());			// zalozime hash startu, aby se uz nepridaval
	pocetKrokuVListu++;
	cout << pocetKrokuVListu << endl;
	// show(); // kazi frontu spravne cesty
	while (moznostiCesty->count() != 0) {
		moznostiCesty = dropMovesInAllPaths(moznostiCesty);				// z bodu ziska nove moznosti jak pokracovat (podle hashe)
		saveState(moznostiCesty->get(0));								// aktualni bod je pokracovani trasy
		hashPrvkuSeznamuCesty->add(moznostiCesty->get(0));				// a ten aktualni oznacime do hashe jako projity (hlavne kvuli dalsim moznym krokum)
		pocetKrokuVListu++;
		cout << pocetKrokuVListu << endl;
		show(); // kazi frontu spravne cesty
		//system("PAUSE");
		moznostiCesty = getPossibleMoves(frontaPrvkuCesty->getData());	// z aktualniho bodu ziska moznosti jak pokracovat
		moznostiCesty = dropMovesInAllPaths(moznostiCesty);				// z bodu ziska jen nove moznosti jak pokracovat (podle hashe)
		if (Point::Equal(frontaPrvkuCesty->getData(), bludiste->getEnd())) {
			return true;
		}
		while (moznostiCesty->count() == 0) {							// rolujeme zpet pokud jsme na konci chodby
			PrvekSeznamu* prvekKMazani = frontaPrvkuCesty->getPredchozi();
			delete frontaPrvkuCesty;
			frontaPrvkuCesty = prvekKMazani;							// posun ve spojitem seznamu nazad
			pocetKrokuVListu--;
			cout << pocetKrokuVListu << endl;
			// show();	// kazi frontu spravne cesty
			// if (frontaPrvkuCesty == nullptr) {
			if (pocetKrokuVListu == 0) {	
				break;	// return false;	kdyz uz neni kam dal se vracet a vycerapali jsme moznosti
			}
			moznostiCesty = getPossibleMoves(frontaPrvkuCesty->getData());	// z aktualniho bodu ziska dalsi smery jak pokracovat
			moznostiCesty = dropMovesInAllPaths(moznostiCesty);				// z bodu ziska jen nove moznosti jak pokracovat (podle hashe)
		}
	}
	return false;
}

void MazeSolver::saveMazeAndSolution(std::string filename) const
{
	ofstream souborKUlozeni;
	souborKUlozeni.open(filename, ios::out);

	char** bludisteZnaky = bludiste->getMaze();
	char trasaZnak = '+';
	char cihlaZnak = (char)MazeTile::Wall;
	char volnoZnak = (char)MazeTile::Empty;
	for (int i = 0; i < bludiste->getR(); i++) {
		for (int j = 0; j < bludiste->getC(); j++)
		{
			PrvekSeznamu* cestaPoJednom = frontaPrvkuCesty;
			while (cestaPoJednom != nullptr) {
				if ((cestaPoJednom->getData().x == i) && (cestaPoJednom->getData().y == j)) {
					bludisteZnaky[i][j] = trasaZnak;
				}
				cestaPoJednom = cestaPoJednom->getPredchozi();
			}

			if (bludisteZnaky[i][j] == trasaZnak) {
				souborKUlozeni << trasaZnak;
			}
			else if (bludisteZnaky[i][j] == cihlaZnak && bludisteZnaky[i][j] != '+') {
				souborKUlozeni << cihlaZnak;	//"#";
			}
			else {
				souborKUlozeni << volnoZnak;	//" ";	//'.'
			}
		}
		souborKUlozeni << endl;
	}
	souborKUlozeni.close();
}

IDynArray<Point>* MazeSolver::getPossibleMoves(Point pt) const
{
	IDynArray<Point>* maticeCesty = new DynArray<Point>();
	char** bludisteZnaky = bludiste->getMaze();
	char cihlaZnak = (char)MazeTile::Wall;
	if (bludiste->isValidPoint(pt)) {
		//NAHORU, 
		if ((bludisteZnaky[pt.x][pt.y - 1] != cihlaZnak) && (pt.y - 1 > 0)) {
			Point tempBod{ pt.x , pt.y - 1 };
			if (bludiste->isValidPoint(tempBod)) {
				maticeCesty->add(tempBod);
			}
		}
		//DOLÙ, 
		if ((bludisteZnaky[pt.x][pt.y + 1] != cihlaZnak) && (pt.y + 1 < bludiste->getC())) {
			Point tempBod{ pt.x , pt.y + 1 };
			if (bludiste->isValidPoint(tempBod)) {
				maticeCesty->add(tempBod);
			}
		}
		//DOLEVA nebo 
		if ((bludisteZnaky[pt.x - 1][pt.y] != cihlaZnak) && (pt.x - 1 > 0)) {
			Point tempBod{ pt.x - 1 , pt.y };
			if (bludiste->isValidPoint(tempBod)) {
				maticeCesty->add(tempBod);
			}
		}
		//DOPRAVA
		if ((bludisteZnaky[pt.x + 1][pt.y] != cihlaZnak) && (pt.x + 1 < bludiste->getR())) {
			Point tempBod{ pt.x + 1 , pt.y };
			if (bludiste->isValidPoint(tempBod)) {
				maticeCesty->add(tempBod);
			}
		}
	}
	return maticeCesty;
}

IDynArray<Point>* MazeSolver::dropMovesInAllPaths(IDynArray<Point>* moves) const
{
	IDynArray<Point>* novePoleNavstivenych = new DynArray<Point>();
	for (int i = 0; i < moves->count(); i++)
	{
		if (!hashPrvkuSeznamuCesty->isPresent(moves->get(i))) {
			novePoleNavstivenych->add(moves->get(i));
		}
	}
	moves->~IDynArray();
	return novePoleNavstivenych;
}

bool MazeSolver::isInCurrentHistory(Point pt) const
{
	PrvekSeznamu* tempPrvek = frontaPrvkuCesty;
	while (tempPrvek != nullptr) {
		if (Point::Equal(tempPrvek->getData(), pt)) {
			return true;
		}
		tempPrvek = tempPrvek->getPredchozi();
	}
	return false;
}

bool MazeSolver::isInAllHistory(Point pt) const
{
	if (hashPrvkuSeznamuCesty->isPresent(pt)) {
		return true;
	}
	return false;
}

void MazeSolver::saveState(Point pt)
{
	PrvekSeznamu* novyPrvek = new PrvekSeznamu(pt, frontaPrvkuCesty);
	frontaPrvkuCesty = novyPrvek;
}

IMaze * MazeSolver::getMaze() const
{
	return this->bludiste;
}

void MazeSolver::show()
{
	char** bludisteZnaky = bludiste->getMaze();
	char trasaZnak = '+';
	char cihlaZnak = (char)MazeTile::Wall;
	char volnoZnak = (char)MazeTile::Empty;
	for (int i = 0; i < bludiste->getR(); i++) {
		for (int j = 0; j < bludiste->getC(); j++)
		{
			PrvekSeznamu* cestaPoJednom = frontaPrvkuCesty;
			while (cestaPoJednom != nullptr) {
				if ((cestaPoJednom->getData().x == i) && (cestaPoJednom->getData().y == j)) {
					bludisteZnaky[i][j] = trasaZnak;
				}
				cestaPoJednom = cestaPoJednom->getPredchozi();
			}

			if (bludisteZnaky[i][j] == trasaZnak) {
				cout << static_cast<char>(176);	// trasaZnak;
			}
			else if (bludisteZnaky[i][j] == cihlaZnak && bludisteZnaky[i][j] != '+') {
				cout << static_cast<char>(219);	//cihlaZnak;	//"#";
			}
			else {
				cout << ' ';	//volnoZnak;	//" ";	//'.'
			}
		}
		cout << endl;
	}
}
