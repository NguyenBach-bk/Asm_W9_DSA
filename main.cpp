#include <ctime>
#include <iostream>

// Cau truc node cua file trong danh sach
struct file_node
{
  std::string file_name;         // Ten file
  size_t file_size;              // Kich thuoc file (MB)
  std::time_t modification_time; // Thoi gian
  file_node *next;               // Con tro node tiep theo

  // Constructor khoi tao file
  file_node (std::string name, size_t size, std::time_t time)
      : file_name (name), file_size (size), modification_time (time),
        next (nullptr)
  {
  }
};

// Lien ket file trong node
struct file_list
{
  file_node *head; // Con tro dau cua danh sach

  // Constructor khoi tao danh sach rong
  file_list () : head (nullptr) {}

  // Them file dua vao thoi gian thuc va vi tri
  void
  ins_sorted_file (const std::string &name, size_t size, std::time_t time)
  {
    file_node *new_node = new file_node (name, size, time);
    if (!head || difftime (head->modification_time, time) > 0)
      {
        new_node->next = head;
        head = new_node;
      }
    else
      {
        file_node *current = head;
        while (current->next
               && difftime (current->next->modification_time, time) < 0)
          {
            current = current->next;
          }
        new_node->next = current->next;
        current->next = new_node;
      }
  }

  // Tinh tong kich thuoc cac file
  size_t
  get_size () const
  {
    size_t total_size = 0;
    file_node *current = head;
    while (current)
      {
        total_size += current->file_size;
        current = current->next;
      }
    return total_size;
  }

  // Loai bo cac file co kich thuoc nho nhat trong day de vua bo nho
  void
  trim_size (size_t max_size)
  {
    while (get_size () > max_size)
      {
        file_node *min_node = head;
        file_node *min_prev = nullptr;
        file_node *current = head;
        file_node *prev = nullptr;
        // Tim file kich thuoc nho nhat
        while (current)
          {
            if (current->file_size < min_node->file_size)
              {
                min_node = current;
                min_prev = prev;
              }
            prev = current;
            current = current->next;
          }
        // Loai bo file co kich thuoc nho nhat
        if (min_prev)
          {
            min_prev->next = min_node->next;
          }
        else
          {
            head = min_node->next;
          }
        delete min_node;
      }
  }

  // In danh sach cac file
  void
  print_list () const
  {
    file_node *current = head;
    while (current)
      {
        std::cout << "File: " << current->file_name
                  << ", Kich thuoc: " << current->file_size
                  << " MB, Thoi gian: "
                  << std::ctime (&current->modification_time);
        current = current->next;
      }
  }
};

// Cho file vao danh sach, doi ten de de nhan biet
void
copy_insert (file_list &list, const std::string &source,
             const std::string &destination, size_t size, std::time_t time)
{

  std::cout << "Sao chep, doi ten file tu " << source << " sang " << destination << "\n";

  list.ins_sorted_file (destination, size, time);
}

int
main ()
{
  file_list fileList;

  // Cho file vao
  fileList.ins_sorted_file ("Part1.rar", 32768, std::time (nullptr) - 100);
  fileList.ins_sorted_file ("Part2.rar", 2000, std::time (nullptr) - 200);
  fileList.ins_sorted_file ("Part3.rar", 500, std::time (nullptr) - 50);

  // Hien thi danh sach cac file
  std::cout << "Danh sach file hien tai:\n";
  fileList.print_list ();

  // Copy file
  copy_insert (fileList, "file_chua_copy.rar", "file_da_copy.rar", 1500,
               std::time (nullptr) - 150);

  // Hien thi file sau khi copy
  std::cout << "\nDanh sach file sau khi sao chep:\n";
  fileList.print_list ();

  // Loai bo cac file khong can thiet neu can
  fileList.trim_size (static_cast<size_t> (32) * 1024);

  // Hien thi cac file sau khi loai bo cac file kich thuoc nho nhat
  std::cout << "\nDanh sach file sau khi loai bo file thua:\n";
  fileList.print_list ();

  return 0;
}
