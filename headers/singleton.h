#ifndef CONFIGURATION_MANGER
#define CONFIGURATION_MANGER 1

#include <string.h>

#include <vector>

using namespace std;

/*

 - Saying that we need only ONE instance from this class, may trigger what?
 - Static object: Shared object among all instances
 - Now let's create a static instance to be shared
 - But still users can create objects!
 - The trick is to make the class constructor private!
 - This way no one can create objects!
 - But???? Ok, give him a function to return your static object

 - You just learned Singleton Design Pattern :)

 */

class ConfigurationManger {
 private:
  string configurationPath;
  vector<string> serversIPs;
  string AWBServiceURL;
  bool isLoaded = false;

  // Private constructor! No one can create instances of this time (or even
  // default one)
  ConfigurationManger(string configPath) : configurationPath(configPath){};

  // Our shared instance
  static ConfigurationManger* configMan;

 public:
  // Give public method to return the static (shared) instance
  static ConfigurationManger* getInstance(const string& value);
  static void freeInstance();
  void load();
  string getAWBServiceURL();
  ~ConfigurationManger();
};

#endif