//File: cdcatalogue.cpp
//Author: Duc-Phuong Nguyen (pdnguyen@sfu.ca)
//Date: 2016-01-20
//Description: Implementation of a CDCatalogue class to be used for CMPT 225 assignment #1

#include "cdcatalogue.h"

void CDCatalogue::CopyArray(const CDCatalogue& cat) {
	maxsize = cat.maxsize;
	cds = new CD [maxsize];

	numcds = cat.numcds;
	for (int i = 0; i < numcds; i ++)
		cds[i] = cat.cds[i];
}

//Default constructor
CDCatalogue::CDCatalogue() {
	maxsize = 4;
	cds = new CD [maxsize];
	numcds = 0;
}

//Copy constructor
CDCatalogue::CDCatalogue(const CDCatalogue& cat) {
	CopyArray(cat);
}

//Destructor
CDCatalogue::~CDCatalogue() {
	delete [] cds;
}

//Insert
bool CDCatalogue::Insert(CD disc) {
	if (Find(disc) != -1) return false;

	if (numcds == maxsize) {
		CD* temp = cds;

		maxsize *= 2;
		cds = new CD [maxsize];
		for (int i = 0; i < numcds; i ++)
			cds[i].Update(temp[i].GetArtist(),temp[i].GetAlbum());

		delete [] temp;
	}
	
	cds[numcds].Update(disc.GetArtist(),disc.GetAlbum());
	numcds ++;

	return true;
}

//Remove
bool CDCatalogue::Remove(CD disc) {
	int num = Find(disc);
	if (num == -1) return false;

	int last = numcds - 1;
	cds[num].Update(cds[last].GetArtist(),cds[last].GetAlbum());
	numcds --;

	return true;
}

int CDCatalogue::Find(CD disc) const {
	for (int i = 0; i < numcds; i ++) 
		if (cds[i] == disc) return i;
	
	return -1;
}

bool CDCatalogue::Boycott(string dontlikeanymore) {
	if (dontlikeanymore == "") return false;
	bool exist = false;
	int i = 0;
	while (i < numcds) {
		if (cds[i].GetArtist() == dontlikeanymore) {
			int last = numcds - 1;
			cds[i].Update(cds[last].GetArtist(),cds[last].GetAlbum());
			numcds --;
		
			exist = true;
		} else i ++;
	}

	return exist;
}

int CDCatalogue::Count() const {
	return numcds;
}

CDCatalogue CDCatalogue::Join(const CDCatalogue& cat) const {
	CDCatalogue result;
	result.maxsize = maxsize + cat.maxsize;
	result.cds = new CD [result.maxsize];

	result.numcds = numcds;
	for (int i = 0; i < numcds; i ++)
		result.cds[i].Update(cds[i].GetArtist(),cds[i].GetAlbum());

	for (int i = 0; i < cat.numcds; i ++)
		if (result.Find(cat.cds[i]) == -1) {
			result.cds[result.numcds].Update(cat.cds[i].GetArtist(),cat.cds[i].GetAlbum());
			result.numcds ++;
		}

	return result;
}

CDCatalogue CDCatalogue::Common(const CDCatalogue& cat) const {
	CDCatalogue result;
	result.maxsize = maxsize;

	result.numcds = 0;
	for (int i = 0; i < numcds; i ++) 
		if (cat.Find(cds[i]) != -1) {
			result.cds[result.numcds].Update(cds[i].GetArtist(),cds[i].GetAlbum());
			result.numcds ++;
		}

	return result;
}

CDCatalogue CDCatalogue::Split(const CDCatalogue& cat) const {
	CDCatalogue result;
	result.maxsize = maxsize;

	result.numcds = 0;
	for (int i = 0; i < numcds; i ++) 
		if (cat.Find(cds[i]) == -1) {
			result.cds[result.numcds].Update(cds[i].GetArtist(),cds[i].GetAlbum());
			result.numcds ++;
		}

	return result;
}