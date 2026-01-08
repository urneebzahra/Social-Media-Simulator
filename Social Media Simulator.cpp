#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//GLOBAL DATA 
const int MAX_POSTS = 10;//Maximum 10 posts allowed
string posts[MAX_POSTS]; //Stores post text
int likes[MAX_POSTS]; //Stores Every post's like
int postCount = 0; // it counts the posts numbers
//LOAD POSTS 
void loadPosts()//used to load old posts from the file
{
    ifstream file("posts.txt"); //Used to create the file
    if (!file) // if file is not made, function closes and returns
        return;
    file >> postCount; //Total posts read
    file.ignore(); //skips New line
    for (int i = 0; i < postCount; i++)
    {
        getline(file, posts[i]);// 2 arguments are passed name of file and array of post
        file >> likes[i]; //read likes
        file.ignore();//skips New line
    }
    file.close();// Closes the file
}
//SAVE POSTS 
void savePosts()
{
    ofstream file("posts.txt");// Opens a file in write mode
    file << postCount << endl; // Saves total posts
    for (int i = 0; i < postCount; i++)// As you know posts[i] and likes[i] are arrays to mamipulate this we use arrays 
    {
        file << posts[i] << endl; // saves every post (indivisually)
        file << likes[i] << endl; // saves every like (indivisually)
    }
    file.close(); // Closes the file
}
// SIGNUP 
void signup()
{
    string user, pass;
    cout <<endl<<"---- SIGN UP ----"<<endl;
    cout << "Enter username: ";
    cin >> user;
    cout << "Enter password: ";
    cin >> pass;
    ofstream file("users.txt", ios::app); // Adds new data to the file (ios::app) "app" "Use to append" ios"Input output stream"
    file << user << " " << pass << endl; //Saves username and password to the file
    file.close();
    cout << "Account created successfully!"<<endl;
}
//LOGIN 
bool login()
{
    string username, password, u, p; //u for username and p for password
    cout << endl << "--- LOGIN ---"<< endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    ifstream file("users.txt"); //Opens the user file
    while (file >> u >> p) // Reads every user's Username & Password
    {
        if (u == username && p == password) // Checks that the username & Password entered earlier is same as the username & Password entered now
        {
            file.close(); // if yes then login success!!!
            cout << "Login successful!" << endl;
            return true; // Opens dashboard
        }
    }
    file.close();
    cout << "Invalid username or password!" << endl; // else print "Invalid username or password!" 
    return false;
}
//CREATE POST
void createPost()
{
    if (postCount >= MAX_POSTS) // Checks if posts count donot exceed max posts
    {
        cout << "Post limit reached!" << endl;
        return;
    }
    cin.ignore();
    cout << "Write your post: ";
    getline(cin, posts[postCount]); // user enters a complete line
    likes[postCount] = 0; // new post like = 0
    postCount++; // total post count increases
    savePosts(); // Save files 
    cout << "Post created successfully!" << endl;
}
//VIEW POSTS
void viewPosts()
{
    if (postCount == 0) // If no post is available or posted
    {
        cout << "No posts available!" << endl; 
        return;
    }
    for (int i = 0; i < postCount; i++)
    {
        cout << endl <<"Post ID: " << i; // shows id of posts
        cout << endl << posts[i];
        cout << endl << "Likes: " << likes[i] << endl; // Shows posts and likes
    }
}
// LIKE POST 
void likePost()
{
    int id;
    viewPosts();
    cout << "Enter Post ID to like: ";
    cin >> id;
    if (id < 0 || id >= postCount)
    {
        cout << "Invalid Post ID!"<<endl;
        return;
    }
    else
    likes[id]++;
    savePosts();
    cout << "Post liked!\n";
}
//DELETE POST 
void deletePost()
{
    int id;
    viewPosts();
    cout << "Enter Post ID to delete: ";
    cin >> id;
    if (id < 0 || id >= postCount)
    {
        cout << "Invalid Post ID!\n";
        return;
    }
    for (int i = id; i < postCount - 1; i++)
    {
        posts[i] = posts[i + 1];
        likes[i] = likes[i + 1];
    }
    postCount--;
    savePosts();
    cout << "Post deleted!\n";
}
//DASHBOARD 
void dashboard()
{
    int choice;
    do
    {
        cout << endl << "---- META THREADS DASHBOARD ----";
        cout << endl << "1. Create Post";
        cout << endl << "2. View Posts";
        cout << endl << "3. Like Post";
        cout << endl << "4. Delete Post";
        cout << endl << "5. Logout";
        cout << endl << "Enter choice: ";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice!\n";
            continue;
        }
        switch (choice)
        {
        case 1: createPost(); break;
        case 2: viewPosts(); break;
        case 3: likePost(); break;
        case 4: deletePost(); break;
        case 5: cout << "Logged out!\n"; break;
        default: cout << "Invalid option!\n";
        }
    } while (choice != 5);
}
//MAIN FUNCTION 
int main()
{
    loadPosts();
    int choice;
    cout << "===== META THREADS (CONSOLE SIMULATOR) ====="<<endl;
    do
    {
        cout << endl << "1. Signup";
        cout << endl << "2. Login";
        cout << endl << "3. Exit";
        cout << endl << "Enter choice: ";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice!\n";
            continue;
        }
        switch (choice)
        {
        case 1: signup(); break;
        case 2:
            if (login())
                dashboard();
            break;
        case 3: cout << "Goodbye!" << endl;
	    break;
        default: cout << "Invalid choice!" << endl;
        }
    } while (choice != 3);
    return 0;
}
