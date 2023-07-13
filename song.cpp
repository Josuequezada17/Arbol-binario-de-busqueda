#include <iostream>
#include "song.hpp"

using namespace std;

Song::Song() : artista(), nameInterpeter(), cancion(""), MP3(""), ranking("") { }

Name Song::getArtista() const {
  return artista;
  }

Name Song::getNameInterpeter() const {
  return nameInterpeter;
  }

string Song::getCancion() const {
  return cancion;
  }

string Song::getMP3() const {
  return MP3;
  }

string Song::getRanking() const {
  return ranking;
  }

string Song::toString() const {
  string result;

    result += "|Song: ";
    result += cancion;
    result.resize(25,' ');
    result += " |Artist: ";
    result += artista.toString();
    result.resize(60, ' ');
    result += " |Rank: ";
    result += ranking;
    result.resize(70, ' ');
    result += " |Interpeter: ";
    result += nameInterpeter.toString();
    result.resize(115, ' ');
    result += " | ";
    result += MP3;
    result.resize(135, ' ');
    result += " | ";

  return result;
  }

void Song::setArtista(const Name& a) {
  artista = a;
  }

void Song::setNameInterpeter(const Name& ni) {
  nameInterpeter = ni;
  }

void Song::setCancion(const string& c) {
  cancion = c;
  }

void Song::setMP3(const string& mp) {
  MP3 = mp;
  }

void Song::setRanking(const string& r) {
  ranking = r;
  }

bool Song::operator == (const Song& c) const {
  return cancion == c.cancion;
  }

bool Song::operator != (const Song& c) const {
  return !(*this == c);
  }

bool Song::operator > (const Song& c) const {
  return !(*this <= c);
  }

bool Song::operator >= (const Song& c) const {
  return !(*this < c);
  }

bool Song::operator < (const Song& c) const {
  return cancion < c.cancion;
  }

bool Song::operator <= (const Song& c) const {
  return *this < c or *this == c;
  }

int Song::compareBySong(const Song& a, const Song& b) {
  return a.cancion.compare(b.cancion);
  }

int Song::compareByArtist(const Song& a, const Song& b) {
  return a.artista.toString().compare(b.artista.toString());
  }

int Song::compareByInterpeter(const Song& a, const Song& b) {
  return a.nameInterpeter.toString().compare(b.nameInterpeter.toString());
  }

int Song::compareByRanking(const Song& a, const Song& b) {
  return a.ranking.compare(b.ranking);
  }

ostream& operator << (ostream& os, const Song &s) {
  os << s.artista        << '|'
     << s.nameInterpeter << '|'
     << s.cancion        << '|'
     << s.MP3            << '|'
     << s.ranking        << '*' << endl;
  return os;
  }

istream& operator >> (istream& is, Song& s) {
  is >> s.artista;
  is >> s.nameInterpeter;
  getline(is, s.cancion, '|');
  getline(is, s.MP3, '|');
  getline(is, s.ranking, '*');
  return is;
  }
