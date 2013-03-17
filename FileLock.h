#include <string>
using namespace std;
class FileLock
{
        public:
            static bool add_lock(string path);
            static bool remove_locks();
        private:
            static bool lock(string path);
            static bool unlock(string path);
};
