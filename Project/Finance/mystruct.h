#ifndef MYSTRUCT_H
#define MYSTRUCT_H

class QLabel;

struct label_list {
    QLabel *label;
    struct label_list *next;
};

#endif // MYSTRUCT_H
