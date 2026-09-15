# Hospital Patient Queue Management System (C)

A terminal-based priority queue application written in C that handles patient registration, triage prioritization, treatment tracking, and patient search functionality using linked lists.

## Features

- **Priority Queue Insertion**: Automatically places new patients in the waiting list based on urgency level (Priority 1: Critical > Priority 2: Serious > Priority 3: Normal).
- **Patient Registration**: Assigns an auto-incrementing ID (starting at `101`) and records name, age, disease, and priority.
- **Treatment Processing**: Removes the highest-priority patient from the waiting queue and shifts their record to the treated list with status `"Treated"`.
- **Dual-List Tracking**: Maintains separate linked lists for active waiting patients and completed treatments.
- **Search Capability**: Allows searching by either Patient ID or Patient Name across both active waiting and treated records.
- **Buffer Safety**: Uses customized input cleaning to prevent buffer overflow and input skipping issues during `scanf` and `fgets` execution.

## Data Structures Used

- **`Patient`**: A singly linked list node for active queue storage containing patient details, assigned priority, and a pointer to the next node.
- **`TreatedPatient`**: A singly linked list node for historical tracking containing ID, name, disease, status, and a pointer to the next node.

## Running the Program

### Steps

Run the compiled executable:

```bash
# On Linux / macOS
./hospital_queue

# On Windows
hospital_queue.exe
