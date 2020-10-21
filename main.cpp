#include <iostream>
#include <map>
#include <vector>

using namespace std;

enum class TaskStatus {
  NEW,
  IN_PROGRESS,
  TESTING,
  DONE
};


using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
 public:
  void AddNewTask(const string& person) {
    person_to_tasks[person][TaskStatus::NEW]++;
  }

  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) const {
    return  person_to_tasks.at(person);
  }

  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count) {
    map<TaskStatus, int> updated_tasks, untouched_tasks, updated_tasks_copy, tasks;
    tasks = person_to_tasks[person];
    int counter = task_count;

    while (counter--) {
      if (tasks[TaskStatus::NEW] > 0) {
        tasks[TaskStatus::NEW]--;
        updated_tasks[TaskStatus::IN_PROGRESS]++;
        continue;
      }
      if (tasks[TaskStatus::IN_PROGRESS] > 0) {
        tasks[TaskStatus::IN_PROGRESS]--;
        updated_tasks[TaskStatus::TESTING]++;
        continue;
      }
      if (tasks[TaskStatus::TESTING] > 0) {
        tasks[TaskStatus::TESTING]--;
        updated_tasks[TaskStatus::DONE]++;
        continue;
      }
    }
    updated_tasks_copy = updated_tasks;
    if (person_to_tasks[person][TaskStatus::NEW] && person_to_tasks[person][TaskStatus::NEW] - updated_tasks_copy[TaskStatus::IN_PROGRESS]) {
      untouched_tasks[TaskStatus::NEW] = person_to_tasks[person][TaskStatus::NEW] - updated_tasks_copy[TaskStatus::IN_PROGRESS];
    }
    if (person_to_tasks[person][TaskStatus::IN_PROGRESS] && person_to_tasks[person][TaskStatus::IN_PROGRESS] - updated_tasks_copy[TaskStatus::TESTING]) {
      untouched_tasks[TaskStatus::IN_PROGRESS] = person_to_tasks[person][TaskStatus::IN_PROGRESS] - updated_tasks_copy[TaskStatus::TESTING];
    }
    if (person_to_tasks[person][TaskStatus::TESTING] && person_to_tasks[person][TaskStatus::TESTING] - updated_tasks_copy[TaskStatus::DONE]) {
      untouched_tasks[TaskStatus::TESTING] = person_to_tasks[person][TaskStatus::TESTING] - updated_tasks_copy[TaskStatus::DONE];
    }

//    if (updated_tasks.count(TaskStatus::IN_PROGRESS)) {
//      untouched_tasks[TaskStatus::NEW] = tasks[TaskStatus::NEW];
//    }
//    if (updated_tasks.count(TaskStatus::TESTING)) {
//      untouched_tasks[TaskStatus::IN_PROGRESS] = tasks[TaskStatus::IN_PROGRESS];
//    }
//    if (updated_tasks.count(TaskStatus::DONE)) {
//      untouched_tasks[TaskStatus::TESTING] = tasks[TaskStatus::TESTING];
//    }

    for (auto [status, count] : tasks) {
      person_to_tasks[person][status] = count;
    }
    for (auto [status, count] : updated_tasks) {
      person_to_tasks[person][status] += count;
    }
    TasksInfo copy = person_to_tasks[person];
    for (auto& [status, count] : copy) {
      if (!count) {
        person_to_tasks.at(person).erase(status);
      }
    }
    return tie(updated_tasks, untouched_tasks);
  }

 private:
  map<string, map<TaskStatus, int>> person_to_tasks;
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
       ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
       ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
       ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
  TeamTasks tasks;
  for (int i = 0; i < 5; ++i) {
    tasks.AddNewTask("Ivan");
  }

  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

  TasksInfo updated_tasks, untouched_tasks;

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 5);
  cout << "\n";
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "\n";
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);
  cout << "\n";

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 5);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "\n";
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);
  cout << "\n";

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 1);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "\n";
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);
  cout << "\n";

  for (int i = 0; i < 5; ++i) {
    tasks.AddNewTask("Ivan");
  }
  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "\n";
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);
  cout << "\n";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 4);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "\n";
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);
  cout << "\n";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));


  return 0;
}
