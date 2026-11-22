#include <iostream>
#include <string>
#include "algorithms.h"
#include "data_structures.h"

using namespace std;

struct Post {
    int likes;
    string post_name;

    bool operator<(const Post& right) const {
        return likes < right.likes;
    }
};

struct PostAnalyser {
    int batch_size;
    LinkedList<AVLTree<Post>*> batches;

    PostAnalyser(int n) {
        batch_size = n;
    }

    ~PostAnalyser() {
        Node<AVLTree<Post>*>* current = batches.first_node;
        while (current != nullptr) {
            delete current->item;
            current = current->next_node;
        }
    }

    void add_batch(Post* post_batch) {
        Post* batch_copy = new Post[batch_size];
        for (int i = 0; i < batch_size; i++) {
            batch_copy[i] = post_batch[i];
        }

        merge_sort(batch_copy, batch_size);

        AVLTree<Post>* tree = new AVLTree<Post>;
        tree->build_from_sorted_array(batch_copy, batch_size);
        batches.append(tree);

        delete[] batch_copy;
    }

    void remove_post(Post post) {
        Node<AVLTree<Post>*>* current = batches.first_node;
        while (current != nullptr) {
            bool removed = current->item->remove(post);
            if (removed) {
                return;
            }
            current = current->next_node;
        }
    }

    Post* least_popular_over_threshold(int threshold) {
        Post target;
        target.likes = threshold;
        target.post_name = "";

        Post* best = nullptr;
        Node<AVLTree<Post>*>* current = batches.first_node;

        while (current != nullptr) {
            Post* candidate = current->item->least_over(target);
            if (candidate != nullptr && (best == nullptr || candidate->likes < best->likes)) {
                best = candidate;
            }
            current = current->next_node;
        }

        return best;
    }
};

int ontrack_test() {
    int n;
    cout << "Enter the batch size:" << endl;
    cin >> n;
    PostAnalyser analyser(n);

    string menu = "1. Add a batch\n2. Remove a post\n3. Find least popular post over a threshold\n4. See the menu again\n5. Quit";
    int command = 4;
    while (command != 5) {
        if (command == 1) {
            Post* batch_post = new Post[n];
            for (int i = 0; i < n; i++) {
                cout << "Enter likes for post " << i << ":" << endl;
                int likes;
                cin >> likes;

                cout << "Enter post name for post " << i << ":" << endl;
                string post_name;
                cin >> post_name;

                batch_post[i].likes = likes;
                batch_post[i].post_name = post_name;
            }
            analyser.add_batch(batch_post);
            delete[] batch_post;
        } else if (command == 2) {
            cout << "Enter likes of the post to remove:" << endl;
            int likes;
            cin >> likes;

            Post post;
            post.likes = likes;
            post.post_name = "To be deleted";
            analyser.remove_post(post);
        } else if (command == 3) {
            cout << "Enter threshold:" << endl;
            int threshold;
            cin >> threshold;
            Post* result = analyser.least_popular_over_threshold(threshold);
            if (result == nullptr) {
                cout << "No such post exists" << endl;
            } else {
                cout << "Post found with " << result->likes << " likes" << endl;
            }
        } else if (command == 4) {
            cout << menu << endl;
        }

        cout << "Enter command (1-5):" << endl;
        cin >> command;
        if (!cin) {
            cout << "ERROR: could not read next command" << endl;
            return 1;
        }
    }
    return 0;
}

int main(int argc, char** argv) {
    if (argc != 1) {
        return ontrack_test();
    }

    return 0;
}
