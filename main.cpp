#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

//Here we store all of our player information
class PlayerInformation
{
private:
	int id;
	std::string name, dob, country, email;
public:

	int getId() { return id; }
	void setId(int _id) { id = _id; }
	std::string getName() { return name; }
	void setName(std::string _name) { name = _name; }
	std::string getDob() { return dob; }
	void setDob(std::string _dob) { dob = _dob; }
	std::string getCountry() { return country; }
	void setCountry(std::string _country) { country = _country; }
	std::string getEmail() { return email; }
	void setEmail(std::string _email) { email = _email; }
};

//Here we store all of our player game data
class PlayerGameData
{
private:
	int score1, score2, score3, currentLevel, remainingLives, bulletCount, maxLevelReached;

public:
	int getScore1() { return score1; }
	void setScore1(int _score1) { score1 = _score1; }
	int getScore2() { return score2; }
	void setScore2(int _score2) { score2 = _score2; }
	int getScore3() { return score3; }
	void setScore3(int _score3) { score3 = _score3; }
	int getCurrentLevel() { return currentLevel; }
	void setCurrentLevel(int _currentLevel) { currentLevel = _currentLevel; }
	int getRemainingLives() { return remainingLives; }
	void setRemainingLives(int _remainingLives) { remainingLives = _remainingLives; }
	int getBulletCount() { return bulletCount; }
	void setBulletCount(int _bulletCount) { bulletCount = _bulletCount; }
	int getMaxLevelReached() { return maxLevelReached; }
	void setMaxLevelReached(int _maxLevelReached) { maxLevelReached = _maxLevelReached; }
};

//Here we store all of our player preferences
class PlayerPreferences
{
private:
	std::string language;
	int volumeLevel, graphicQuality, difficultyLevel;

public:
	std::string getLanguage() { return language; }
	void setLanguage(std::string _language) { language = _language; }
	int getVolumeLevel() { return volumeLevel; }
	void setVolumeLevel(int _volumeLevel) { volumeLevel = _volumeLevel; }
	int getGraphicQuality() { return graphicQuality; }
	void setGraphicQuality(int _graphicQuality) { graphicQuality = _graphicQuality; }
	int getDifficultyLevel() { return difficultyLevel; }
	void setDifficultyLevel(int _difficultyLevel) { difficultyLevel = _difficultyLevel; }
};

//This is where we create JSON objects and store player preferences,etc 
//in them using our get functions defined in each corressponding class
class JSONCommunicator
{
public:
	JSONCommunicator(PlayerPreferences *_pP, PlayerInformation *_pI, PlayerGameData *_pgD) { pP = _pP; pI = _pI; pgD = _pgD; };
	json* pP_ptr;
	PlayerPreferences *pP;
	PlayerGameData *pgD;
	PlayerInformation *pI;

	json playerPref()
	{
		json playerPreferences =
		{
			{ "Language: ", pP->getLanguage() },
			{ "Volume Level: ", pP->getVolumeLevel() },
			{ "Graphic Quality: ", pP->getGraphicQuality() },
			{ "Difficulty Level: ", pP->getDifficultyLevel() }
		};
		return playerPreferences;
	}

	json playerInfo()
	{
		json playerInformation =
		{
			{ "25345845", pI->getId() },
			{ "Dolores", pI->getName() },
			{ "07/18/1988", pI->getDob() },
			{ "WestWorld", pI->getCountry() },
			{ "Dolores@westworld.com", pI->getEmail() }
		};
		return playerInformation;
	}

	json playerGD()
	{
		json playerGameData =
		{
			{ "947", pgD->getScore1() },
			{ "1672", pgD->getScore2() },
			{ "8262", pgD->getScore3() },
			{ "3", pgD->getCurrentLevel() },
			{ "1", pgD->getRemainingLives() },
			{ "12", pgD->getBulletCount() },
			{ "3", pgD->getMaxLevelReached() }
		};
		return playerGameData;
	}
};

//Here we call an instance of each of our player classes and set the values
//we wish to store in the JSON object
int main()
{
	PlayerPreferences *pP = new PlayerPreferences();
	pP->setLanguage("EN");
	pP->setVolumeLevel(20);
	pP->setGraphicQuality(100);
	pP->setDifficultyLevel(5);

	PlayerGameData *pgD = new PlayerGameData();
	pgD->setScore1(947);
	pgD->setScore2(1672);
	pgD->setScore3(8262);
	pgD->setCurrentLevel(3);
	pgD->setRemainingLives(1);
	pgD->setBulletCount(12);
	pgD->setMaxLevelReached(3);

	PlayerInformation *pI = new PlayerInformation();
	pI->setId(25345845);
	pI->setName("Dolores");
	pI->setDob("07/18/1988");
	pI->setCountry("WestWorld");
	pI->setEmail("Dolores@westworld.com");

	//Here we open the player preferences file
	//We pass in the values that we have just set (above)
	//After data is passed in, we close the file
	std::ofstream myFile;
	myFile.open("playerPreferences.txt");
	myFile <<
		"Player Preferences" << "\n" <<
		"Language: " << pP->getLanguage() << "\n" <<
		"Volume Level : " << pP->getVolumeLevel() << "\n" <<
		"Graphic Quality: " << pP->getGraphicQuality() << "%" << "\n" <<
		"Difficulty Level: " << pP->getDifficultyLevel();
	myFile.close();

	std::ofstream myFile1;
	myFile1.open("playerGameData.txt");
	myFile1 <<
		"Player Game Data" << "\n" <<
		"Level_1 Score: " << pgD->getScore1() << "\n" <<
		"Level_2 Score: " << pgD->getScore2() << "\n" <<
		"Level_3 Score: " << pgD->getScore3() << "\n" <<
		"Current Level: " << pgD->getCurrentLevel() << "\n" <<
		"Remaining Lives: " << pgD->getRemainingLives() << "\n" <<
		"Difficulty Level: " << pgD->getBulletCount() << "\n" <<
		"Max Level Reached: " << pgD->getMaxLevelReached();

	myFile1.close();

	std::ofstream myFile2;
	myFile2.open("playerInformation.txt");
	myFile2 <<
		"Player Information" << "\n" <<
		"ID: " << pI->getId() << "\n" <<
		"Name: " << pI->getName() << "\n" <<
		"DOB: " << pI->getDob() << "\n" <<
		"Country: " << pI->getCountry() << "\n" <<
		"E-mail: " << pI->getEmail();
	myFile2.close();

	//
	JSONCommunicator *jsc = new JSONCommunicator(pP, pI, pgD);
	std::cout << jsc->playerGD();
	std::cout << jsc->playerInfo();
	std::cout << jsc->playerPref();

	std::ofstream JSONFile;
	JSONFile.open("playerInformation.json");
	JSONFile << jsc->playerInfo();
	JSONFile.close();

	std::ofstream JSONFile1;
	JSONFile1.open("playerGameData.json");
	JSONFile1 << jsc->playerGD();
	JSONFile1.close();

	std::ofstream JSONFile2;
	JSONFile2.open("playerPreferences.json");
	JSONFile2 << jsc->playerPref();
	JSONFile2.close();

	return 0;
}