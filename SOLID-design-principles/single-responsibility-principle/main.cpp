#include <iostream>
#include <boost/lexical_cast.hpp>
#include <fstream>

using namespace std;
using namespace boost;

/**
 * Single responsibility principle states that a class should have a single reason to exist
 *  A class should have a primary responsibility and not assume other responsibilities
 */


struct Journal {
    string title;
    vector<string> entries;

    //Constructor to initialize Journal and set title
    Journal(const string &title) : title(title) {}

    void add_entry(const string& entry) {
        static  int count = 1;
        entries.push_back(lexical_cast<string>(count++) + ": " + entry);
    }


    /**
     * Background:
     * Lets say we would like to save our journal entry.
     * The wrong way to go about this is to add the load and save functionality within the Journal class
     * This is what we are doing below
     *
     * Problem:
     * This gives the Journal class another responsibility/concern.... PERSISTENCE
     * Imagine we have other domain objects that need to load and save data as well
     * We would have to manage persistence within other domain objects in addition to Journal class
     *
     *
     * Remember Separation of Concerns!!!!
     * The Journal should take care of the journal entries and the journal title
     * but if we want to persist things, that should really happen within a separate class
     *
     *
     */

    void save(const string& filename) {
        ofstream ofs(filename);
        for(auto& e: entries) {
            ofs << e << endl;
        }
    }
};

/**
 * One central location where objects are loaded or saved
 * This is a more robost way to implement persistence because as the Persistence Manager grows,
 * all persistence happens within a single place/location in code
 *
 * If we decide to make a change, we only need to make the change within the persistence manager
 * The concern related to persistence is moved out into a separate component
 *
 */
struct PersistenceManager {
    static void save(const Journal& journal, const string& filename) {
        ofstream ofs(filename);
        for(auto& e: journal.entries) {
            ofs << e << endl;
        }
    }
};

int main() {


    // It is the Journal's responsibility to keep the entries inside the Journal
    Journal journal{"Dear Diary"};
    journal.add_entry("I ate a bug");
    journal.add_entry("I laughed today!");

    /**
     * Instead of doing this...
     */

    //journal.save("diary.txt");

    /**
     * We do something like this...
     */

    PersistenceManager persistenceManager;
    persistenceManager.save(journal, "diary.txt");




    return 0;
}
