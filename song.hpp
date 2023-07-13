#ifndef SONG_HPP_INCLUDED
#define SONG_HPP_INCLUDED

#include <iostream>
#include <string>
#include "name.hpp"

class Song {

  private:
    Name artista;
    Name nameInterpeter;
    std::string cancion;
    std::string MP3;
    std::string ranking;

  public:
    Song();

    Name getArtista() const;
    Name getNameInterpeter() const;
    std::string getCancion() const;
    std::string getMP3() const;
    std::string getRanking() const;

    std::string toString() const;

    void setCancion(const std::string&);
    void setMP3(const std::string&);
    void setArtista(const Name&);
    void setNameInterpeter(const Name&);
    void setRanking(const std::string&);

    bool operator == (const Song&) const;
    bool operator != (const Song&) const;
    bool operator > (const Song&) const;
    bool operator >= (const Song&) const;
    bool operator < (const Song&) const;
    bool operator <= (const Song&) const;

    static int compareBySong(const Song&, const Song&);
    static int compareByArtist(const Song&, const Song&);
    static int compareByInterpeter(const Song&, const Song&);
    static int compareByRanking(const Song&, const Song&);

    friend std::ostream& operator << (std::ostream&, const Song&);
    friend std::istream& operator >> (std::istream&, Song&);
  };


#endif // SONG_HPP_INCLUDED
