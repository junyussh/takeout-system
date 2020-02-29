#include <ncurses.h>
#include <form.h>
#include <cstring>
#include <string>
using namespace std;
void Register(WINDOW *);
void MainMenu(WINDOW *);
void CreateShop(WINDOW *);
enum Forms {
    SHOP, USER
};
static char* trim_whitespaces(char *str)
{
	char *end;

	// trim leading space
	while(isspace(*str))
		str++;

	if(*str == 0) // all spaces?
		return str;

	// trim trailing space
	end = str + strnlen(str, 128) - 1;

	while(end > str && isspace(*end))
		end--;

	// write new null terminator
	*(end+1) = '\0';

	return str;
}
void driver(Forms formType, FORM *&form, FIELD **fields, int ch)
{
    switch (ch)
    {
    case KEY_F(2):
			// Or the current field buffer won't be sync with what is displayed
			form_driver(form, REQ_NEXT_FIELD);
			form_driver(form, REQ_PREV_FIELD);
			move(LINES-3, 2);

			for (int i = 0; fields[i]; i++) {
				printw("%s", trim_whitespaces(field_buffer(fields[i], 0)));

				if (field_opts(fields[i]) & O_ACTIVE)
					printw("\"\t");
				else
					printw(": \"");
			}

			refresh();
			pos_form_cursor(form);
			break;

		case KEY_DOWN:
			form_driver(form, REQ_NEXT_FIELD);
			form_driver(form, REQ_END_LINE);
			break;

		case KEY_UP:
			form_driver(form, REQ_PREV_FIELD);
			form_driver(form, REQ_END_LINE);
			break;

		case KEY_LEFT:
			form_driver(form, REQ_PREV_CHAR);
			break;

		case KEY_RIGHT:
			form_driver(form, REQ_NEXT_CHAR);
			break;

		// Delete the char before cursor
		case KEY_BACKSPACE:
		case 127:
			form_driver(form, REQ_DEL_PREV);
			break;

		// Delete the char under the cursor
		case KEY_DC:
			form_driver(form, REQ_DEL_CHAR);
			break;

		default:
			form_driver(form, ch);
			break;
    }
}
void ShopForm(WINDOW *win)
{
    werase(win);
    refresh();
    mvprintw(0, 0, "form");
    mvwprintw(win, 1, 25, "New Shop");
    keypad(stdscr, TRUE);
    FIELD *fields[9];
    // Name
    fields[0] = new_field(1, 10, 1, 3, 0, 0);
    fields[1] = new_field(1, 20, 1, 15, 0, 0);
    // Phone
    fields[2] = new_field(1, 10, 2, 3, 0, 0);
    fields[3] = new_field(1, 20, 2, 15, 0, 0);
    // Address
    fields[4] = new_field(1, 10, 3, 3, 0, 0);
    fields[5] = new_field(1, 20, 3, 15, 0, 0);
    // Password
    fields[6] = new_field(1, 10, 4, 3, 0, 0);
    fields[7] = new_field(1, 20, 4, 15, 0, 0);
    // NULL
    fields[8] = NULL;
    set_field_buffer(fields[0], 0, "Name");
    set_field_buffer(fields[1], 0, "");
    set_field_buffer(fields[2], 0, "Phone");
    set_field_buffer(fields[3], 0, "");
    set_field_buffer(fields[4], 0, "Address");
    set_field_buffer(fields[5], 0, "");
    set_field_buffer(fields[6], 0, "Password");
    set_field_buffer(fields[7], 0, "");
    // Name
    set_field_opts(fields[0], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(fields[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_back(fields[1], A_UNDERLINE);
    // Phone
    set_field_opts(fields[2], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(fields[3], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_back(fields[3], A_UNDERLINE);
    // Address
    set_field_opts(fields[4], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(fields[5], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_back(fields[5], A_UNDERLINE);
    // Password
    set_field_opts(fields[6], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(fields[7], O_VISIBLE | O_EDIT | O_ACTIVE);
    set_field_back(fields[7], A_UNDERLINE);
    // set_field_type(fields[7], new_fieldtype(true, true))
    FORM *form = new_form(fields);
    set_form_win(form, win);
    set_form_sub(form, derwin(win, 0, 0, 2, 2));
    post_form(form);
    box(win, 0, 0);

    refresh();
    wrefresh(win);
    int ch;
    while ((ch = getch()) != KEY_F(1))
    {
        driver(Forms::SHOP, form, fields, ch);
        wrefresh(win);
    }
    unpost_form(form);
    free_form(form);
    for (int i = 0; i < 9; i++)
    {
        free_field(fields[i]);
    }
}
void Register(WINDOW *win)
{
    werase(win);
    refresh();
    int choice, highlight = 0;
    string options[3] = {"New user", "New shop", "Go Back"};

    box(win, 0, 0);
    mvwprintw(win, 1, 25, "Register");
    refresh();
    wrefresh(win);

    keypad(win, true);
    while (true)
    {
        for (int i = 0; i < 3; i++)
        {
            if (i == highlight)
            {
                wattron(win, A_REVERSE);
            }
            mvwprintw(win, 2 + i, 1, options[i].c_str());
            wattroff(win, A_REVERSE);
        }
        choice = wgetch(win);

        switch (choice)
        {
        case KEY_UP:
            highlight = (highlight - 1 + 3) % 3;
            break;
        case KEY_DOWN:
            highlight = (highlight + 1) % 3;
            break;
        default:
            break;
        }
        if (choice == 10)
        {
            break;
        }
    }
    switch (highlight)
    {
    case 1:
        // create shop
        ShopForm(win);
        Register(win);
        break;
    case 2:
        // Go Back
        break;

    default:
        mvprintw(0, 0, "%d", highlight);
        break;
    }
}
void MainMenu(WINDOW *win)
{
    int choice, highlight = 0;
    string options[3] = {"Login", "Register", "Quit"};

    box(win, 0, 0);
    mvwprintw(win, 1, 20, "Takeout Management");
    refresh();
    wrefresh(win);

    keypad(win, true);
    while (true)
    {
        for (int i = 0; i < 3; i++)
        {
            if (i == highlight)
            {
                wattron(win, A_REVERSE);
            }
            mvwprintw(win, 2 + i, 1, options[i].c_str());
            wattroff(win, A_REVERSE);
        }
        choice = wgetch(win);

        switch (choice)
        {
        case KEY_UP:
            highlight = (highlight - 1 + 3) % 3;
            break;
        case KEY_DOWN:
            highlight = (highlight + 1) % 3;
            break;
        default:
            break;
        }
        if (choice == 10)
        {
            break;
        }
    }
    switch (highlight)
    {
    case 1: // Register
        Register(win);
        werase(win);
        refresh();
        MainMenu(win);
        break;

    default:
        break;
    }
    // if (highlight == 0)
    // {
    //     erase();
    //     refresh();
    //     mvprintw(0, 0, "Login");
    // }
}
int main(int argc, char const *argv[])
{

    // initializes screen
    initscr();
    cbreak();
    noecho();

    int y, x, yBeg, xBeg, yMax, xMax;

    getyx(stdscr, y, x);
    getbegyx(stdscr, yBeg, xBeg);
    getmaxyx(stdscr, yMax, xMax);
    mvprintw(yMax / 2, xMax / 2, "Hello");

    int height, width;
    height = 20;
    width = 60;
    WINDOW *win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
    MainMenu(win);
    // mvprintw(0, 0, "Pressed %s", options[highlight].c_str());

    // getch();
    endwin();
    return 0;
}
