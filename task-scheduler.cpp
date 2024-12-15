class Task {
public:
    int id;
    int priority;
    int retryCount;
    int maxRetries;
    unordered_set<int> dependencies;
    
    Task(int id, int priority, int maxRetries)
        : id(id), priority(priority), retryCount(0), maxRetries(maxRetries) {}
    
    virtual ~Task() {}

    virtual bool execute() = 0; // Abstract method for task execution

    virtual void callback(bool success) {
        cout << "Task " << id << " " << (success ? "succeeded" : "failed") << "\n";
    }

    bool operator<(const Task& other) const {
        return priority < other.priority; // Higher priority first
    }
};

class TaskA : public Task {
public:
    TaskA(int id, int priority, int maxRetries)
        : Task(id, priority, maxRetries) {}

    bool execute() override {
        cout << "Executing TaskA " << id << "\n";
        return true; // Simulate success
    }
};

class TaskD : public Task {
public:
    TaskD(int id, int priority, int maxRetries)
        : Task(id, priority, maxRetries) {}

    bool execute() override {
        cout << "Executing TaskD " << id << "\n";
        return false; // Simulate failure for retries
    }
};

class TaskE : public Task {
public:
    TaskE(int id, int priority, int maxRetries)
        : Task(id, priority, maxRetries) {}

    bool execute() override {
        cout << "Executing TaskE " << id << "\n";
        return (rand() % 2 == 0); // Randomly succeed or fail
    }
};

class TaskManager {
private:
    priority_queue<shared_ptr<Task>> taskQueue;
    unordered_map<int, shared_ptr<Task>> allTasks;
    unordered_set<int> completedTasks;
    mutex mutex_;
    condition_variable cv;
    bool stopProcessing = false;

    bool areDependenciesSatisfied(const shared_ptr<Task>& task) {
        for (int dep : task->dependencies) {
            if (completedTasks.find(dep) == completedTasks.end()) {
                return false;
            }
        }
        return true;
    }
    
public:
    void addTask(const shared_ptr<Task>& task) {
        lock_guard<mutex> lock(mutex_);
        allTasks[task->id] = task;
    }

    void start(int numWorkers) {
        for (int i = 0; i < numWorkers; ++i) {
            thread([this] { this->processTasks(); }).detach();
        }
    }

    void stop() {
        lock_guard<mutex> lock(mutex_);
        stopProcessing = true;
        cv.notify_all();
    }
    
    void processTasks() {
        while (true) {
            shared_ptr<Task> taskToExecute;

            {
                unique_lock<mutex> lock(mutex_);
                cv.wait(lock, [this] {
                    return stopProcessing || !allTasks.empty();
                });

                if (stopProcessing) break;

                for (auto it = allTasks.begin(); it != allTasks.end();) {
                    if (areDependenciesSatisfied(it->second)) {
                        taskToExecute = it->second;
                        taskQueue.push(it->second);
                        it = allTasks.erase(it);
                    } else {
                        ++it;
                    }
                }
            }

            while (!taskQueue.empty()) {
                auto task = taskQueue.top();
                taskQueue.pop();

                bool success = false;
                while (task->retryCount <= task->maxRetries) {
                    success = task->execute();
                    if (success) break;
                    task->retryCount++;
                    this_thread::sleep_for(chrono::milliseconds(100));
                }

                {
                    lock_guard<mutex> lock(mutex_);
                    completedTasks.insert(task->id);
                    task->callback(success);
                }

                cv.notify_all();
            }
        }
    }
};
