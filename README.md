# Database Homework 1 (Student management system)
## Task

This is a CLI program that can manage students' information.

We can use this program to add, delete, modify and query following information:
- Student data
- Subjects
- Grades

Also we can find top students whose average grade is higher than a given number.

Task can be found [by this link](https://ati.ttu.ee/wiki/e/index.php/IAG0582_-_Programming_II#3._Homework)

## Usage
### Configure database connection
Go to `functions/cli.h` and set `DB_HOST`, `DB_USER`, `DB_PASS` and `DB_NAME` to your database connection information.

### CLI interface
At the start, will display possible commands. You can use `help` command to display them again. It also displays `>` symbol, which means you can input command.

```
\path\to\homework> ./main.exe
Welcome to the command line interface of the database.
The available commands are:
_______________________________________________
help
ranking
list student   | list grade   | list subject
create student | create grade | create subject
update student | update grade | update subject
delete student | delete grade | delete subject
exit
_______________________________________________

>
```
You can list any type of data by using `list` command. For example, `list subject` will list all students in the database.

```
> list student
Found 46 records:


| Code   | Name       | Surname    | Birthdate  | Avg  |
|--------|------------|------------|------------|------|
| 000049 | Sven       | Keskula    | 1991-06-19 | 3.08 |
| 000055 | Reio       | Aavik      | 1993-09-18 | 4.02 |
| 000148 | Paavo      | Meri       | 1992-04-28 | 3.45 |
| 000150 | Kaur       | Valk       | 1992-09-06 | 4.38 |
.....
```
You can also create, update and delete data by using `create`, `update` and `delete` commands. For example, `create subject` will create a new subject.

```
> create subject
Enter information about subject:
Code: abc1234
Name: Programming
Teacher: John Doe
Credits: 4
Subject created successfully
```
Or modify existing data by using `update` command.

```
> update subject
Enter subject id: 10

Subject ( ID: 10 | Code: abc1234 | Name: Programming | Teacher: John Doe | 4 ects )
Enter information about subject:
Code [abc1234]:
Name [Programming]: Coding
Teacher [John Doe]:         
Credits [4]: 6
Subject updated successfully
```

You can also find top students by using `ranking` command. It will display students whose average grade is higher than a given number.

```
> ranking
Enter minimum grade: 3.2
Found 2 records:


| Code   | Name       | Surname    | Birthdate  | Avg  |
|--------|------------|------------|------------|------|
| 001874 | Ivan       | Symotiuk   | 2005-01-01 | 5.00 |
| 001873 | Jane       | Doe        | 2022-01-01 | 4.10 |

``` 
And exit the program by using `exit` command.

```
> exit
Thank you for using the command line interface of the database.
```

### File structure
As this project is more complex, the code is splitted in more than 3 files. Here is the file structure:

```
.
├── functions
│   ├── cli.h
│   ├── cli.c
│   ├── types.h
│   ├── data
│   │   ├── data.h
│   │   └── data.c
│   ├── forms
│   │   ├── forms.h
│   │   └── forms.c
│   └── lists
│       ├── lists.h
│       └── lists.c
└── main.c
```

In this repository there are also `.setup/` and `.vscode/` folders. These are used for Visual Studio Code and databse setup, and are not needed for the program to work.

The functions are grouped by purpose:
- `main.c` - main function
- `cli.h` and `cli.c` are used for overall CLI interface and navigation
- `data.h` and `data.c` are used for data manipulation
- `forms.h` and `forms.c` are used for user input groups
- `lists.h` and `lists.c` are used for displaying data in tables

