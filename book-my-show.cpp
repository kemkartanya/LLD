#include <iostream>
#include <string>
#include <vector>

using namespace std;

// forward declaration of classes
class Movie;
class Show;
class Theatre;
class Ticket;

// Enums
enum Language {ENGLISH, HINDI};
enum Genre {ACTION, ROMANCE, COMEDY, HORROR};

class Movie {
  string name;
  float ratings;

  Language *language;
  Genre *genre;

  public:
    // constructor
    Movie (string name, Language language, Genre genre) {
      name = name;
      ratings = 0.0;
      language = language;
      genre = genre;
    }

    // getters and setters
    string getName () {
      return name;
    }

    void setName (string name) {
      name = name;
    }

    float getRatings () {
      return ratings;
    }

    void setRatings (float ratings) {
      ratings = ratings;
    }

    Language *getLanguage () {
      return language;
    }

    void setLanguage (Language *language) {
      language = language;
    }

    Genre *getGenre () {
      return genre;
    }

    void setGenre (Genre *genre) {
      genre = genre;
    }
};

class Theatre {
  int id;
  string name;
  string location;
  int capacity;

  vector <Show> shows;

  public :
    Theatre (int id, string name, string location, int capacity, vector <Show> shows) {
      id = id;
      name = name;
      location = location;
      capacity = capacity;
      shows = shows;
    }

    /* Getters and setters
     .
     .
     .
    */
};

class Show {
  int id;
  string showTime;
  int availableSeats;

  Movie *movie;
  Theatre *theatre;

  public:
    Show (int id, string showTime, int availableSeats, Movie *movie, Theatre *theatre) {
      id = id;
      showTime = showTime;
      availableSeats = availableSeats;
      movie = movie;
      theatre = theatre;
    }

    /* Getters and setters
     .
     .
     .
    */
};

class Ticket {
  int id;
  string ownerName;
  int numberOfSeats;
  string bookingTime;

  Show *bookedShow;

  public:
    Ticket (int id, string ownerName, int numberOfSeats, string bookingTime, Show *bookedShow) {
      id = id;
      ownerName = ownerName;
      bookingTime = bookingTime;
      bookedShow = bookedShow;
      numberOfSeats = numberOfSeats;
    }

    /* Getters and setters
     .
     .
     .
    */
};

class User {
  int id;
  string name;

  public:
    User (int id, string name) {
      id = id;
      name = name;
    }

    /* Getters and setters
     .
     .
     .
    */
};

class GuestUser: virtual public User {
  public:
    GuestUser (int id, string name) : User (id, name) {};

    /* Getters and setters
     .
     .
     .
    */
};

class RegisteredUser: virtual public User {
  vector <Ticket> bookingHistory;

  public:
    RegisteredUser (int id, string name) : User (id, name) {};

    /* Getters and setters
     .
     .
     .
    */
};

class BookMyShow {
  vector <User> users;
  vector <Theatre> theatres;

  public:
    BookMyShow (vector <User> users, vector <Theatre> theatres) {
      users = users;
      theatres = theatres;
    }

    /* Getters and setters
     .
     .
     .
    */
};


int main () {
  cout << "Book My Show System" << endl;

  return 0;
}
