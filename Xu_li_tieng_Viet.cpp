#include <iostream>

// Cau truc node luu tru tu va so lan xuat hien
struct word_node
{
  std::string word;
  int count;
  word_node *next;

  word_node (std::string w) : word (w), count (1), next (nullptr) {}
};

// Cau truc danh sach quan ly cac tu
struct word_link_list
{
  word_node *head;

  word_link_list () : head (nullptr) {}

  // Them tu vao danh sach
  void
  insert_word (const std::string &word)
  {
    word_node *current = head;
    word_node *prev = nullptr;
    while (current)
      {
        if (current->word == word)
          {
            current->count++;
            return;
          }
        prev = current;
        current = current->next;
      }
    word_node *new_node = new word_node (word);
    if (prev)
      {
        prev->next = new_node;
      }
    else
      {
        head = new_node;
      }
  }

  // In danh sach tu
  void
  print_list () const
  {
    word_node *current = head;
    while (current)
      {
        std::cout << "Tu: " << current->word
                  << ", So lan xuat hien: " << current->count << std::endl;
        current = current->next;
      }
  }

  // Tim cac tu xuat hien nhieu nhat
  std::string
  find_frequent () const
  {
    word_node *current = head;
    std::string most_frequent;
    int max_count = 0;
    while (current)
      {
        if (current->count > max_count)
          {
            max_count = current->count;
            most_frequent = current->word;
          }
        current = current->next;
      }
    return most_frequent;
  }

  // Loai bo tu lay
  void
  remove_duplicate ()
  {
    word_node *current = head;
    word_node *prev = nullptr;
    while (current)
      {
        if (current->word.length () >= 4
            && current->word.substr (0, current->word.length () / 2)
                   == current->word.substr (current->word.length () / 2))
          {
            std::cout << "Loai bo tu lay: " << current->word << std::endl;
            if (prev)
              {
                prev->next = current->next;
              }
            else
              {
                head = current->next;
              }
            word_node *temp = current;
            current = prev ? prev->next : head;
            delete temp;
          }
        else
          {
            prev = current;
            current = current->next;
          }
      }
  }

  // Dem so tu vung
  int
  count_word () const
  {
    int count = 0;
    word_node *current = head;
    while (current)
      {
        count++;
        current = current->next;
      }
    return count;
  }
};

int
main ()
{
  word_link_list word_list;

  // Nhap cau tu nguoi dung
  std::cout << "Nhap cau tieng Viet: ";
  std::string sentence;
  getline (std::cin, sentence);

  // Tach cac tu tu cau va nhap vao danh sach
  size_t pos = 0;
  std::string delimiter = " ";

  while ((pos = sentence.find (delimiter)) != std::string::npos)
    {
      std::string word = sentence.substr (0, pos);
      word_list.insert_word (word);
      sentence.erase (0, pos + delimiter.length ());
    }
  word_list.insert_word (sentence); // Them tu cuoi cung

  std::cout << "Danh sach tu ban dau:\n";
  word_list.print_list ();

  std::string most_frequent = word_list.find_frequent ();
  std::cout << "Tu xuat hien nhieu nhat: " << most_frequent << std::endl;

  word_list.remove_duplicate ();
  std::cout << "Danh sach tu sau khi loai bo tu lay:\n";
  word_list.print_list ();

  int wordCount = word_list.count_word ();
  std::cout << "So tu trong cau: " << wordCount << std::endl;

  return 0;
}
