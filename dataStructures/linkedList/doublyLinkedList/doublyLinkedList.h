// Author: Moisés Adame-Aguilar
// Creation Date: Octiber 12, 2023.
// Description: A doubly linked list implemented in C++.

#ifndef __DoublyLinkedList
#define __DoublyLinkedList
#pragma once

#include<iostream>
#include<utility>
using namespace std;

template<typename T>
class Node{
    public:
        // -- Attributes
        T data;
        Node<T>* next;
        Node<T>* prev;
        
        // -- Methods
        // Constructor method. 
        Node(T data, Node<T>* next, Node<T>* prev){
            this->data = data;
            this->next = next;
            this->prev = prev;
        }

        void print(){
            cout << this->data << endl;
        }
};

template<typename T>
class DoublyLinkedList{
    public:
        // -- Attributes
        Node<T>* head;
        Node<T>* tail;
        int size;

        // -- Methods
        // Constructor method. 
        DoublyLinkedList(){
            this->head = NULL;
            this->tail = NULL;
            this->size = 0;
        }

        // Method that appends a value to the List's head.
        // Complexity: O(1)
        void addFirst(T data){
            if(head == NULL && tail == NULL){
                head = new Node<T>(data, NULL, NULL);
                tail = head;
            }else{
                Node<T>* newNode = new Node<T>(data, head, NULL);
                head->prev = newNode;
                head = newNode;
            }
            size++;
        }

        // Method that appends a value to the List's tail.
        // Complexity: O(1)
        void addLast(T data){
            if(head == NULL && tail == NULL){
                head = new Node<T>(data, NULL, NULL);
                tail = head;
            }else{
                Node<T>* newNode = new Node<T>(data, NULL, tail);
                tail->next = newNode;
                tail = newNode;
            }
            size++;
        }

        // Method that inserts a given value in a given position.
        // Complexity: O(n)
        void insert(T data, int index){
            if(index < 0 || index > this->size){
                throw -1;
            }else if(index == 0){
                this->addFirst(data);
            }else if(index == this->size){
                this->addLast(data);
            }else{
                Node<T>* temp = this->head;
                for(int i = 0; i < index - 1; i++){
                    temp = temp->next;
                }

                temp->next = new Node<T>(data, temp->next, temp);
                size++;
            }
        }

        // Method that removes the first element in the LinkedList.
        T removeFirst(){
            if(size != 0){
                T returnValue = head->data;
                if(head->next != NULL){
                    Node<T>* temp = head->next;
                    head = temp;
                    head->prev = NULL;

                    if(size == 2){
                        tail = head;
                    }

                }else{
                    head = NULL;
                    tail = NULL;
                }
                size--;
                return returnValue;
            }else{
                throw -1;
            }
        }

        // Method that removes the last element in the LinkedList.
        T removeLast(){
            if(size != 0){
                T returnValue = tail->data;
                if(head->next != NULL){
                    Node<T>* temp = tail->prev;
                    tail = temp;
                    tail->next = NULL;
                }else{
                    head = NULL;
                    tail = NULL;
                }
                size--;
                return returnValue;
            }else{
                throw -1;
            }
        }

        // Method that prints all the elements inside the List.
        void print(bool reverse = false){
            if(reverse){
                Node<T>* aux = tail;
                while(aux != NULL){
                    aux->print();
                    aux = aux->prev;
                }
            }else{
                Node<T>* aux = head;
                while(aux != NULL){
                    aux->print();
                    aux = aux->next;
                }
            }
        }

        // Method that sorts the elements of the list calling Merge Sort algorithm.
        // Complexity: O(n log(n))
        void mergeSort(){
            pair<Node<T>*, Node<T>* > mergedPair;
            mergedPair = this->mergeSort(0, this->size - 1);
            this->head = mergedPair.first;
            this->tail = mergedPair.second;
        }

        // Method that deletes a node for a given index.
        // Complexity: O(n)
        T deleteAt(int index){
            if(index < 0 || index > this->size - 1){
                throw -1;
            }else if(index == 0){
                return this->removeFirst();
            }else if(index == this->size - 1){
                return this->removeLast();
            }else{
                Node<T>* temp = this->head;
                for(int i = 0; i < index - 1; i++){
                    temp = temp->next;
                }

                T returnValue = temp->next->data;
                temp->next = temp->next->next;
                temp->next->prev = temp;
                size--;

                return returnValue;
            }
        }

        // Method that returns the max element in the list.
        // Complexity: O(n)
        T max(){
            T maxValue = head->data;
            Node<T>* aux = head->next;
            
            while(aux != NULL){
                if(aux->data > maxValue){
                    maxValue = aux->data;
                }
                aux = aux->next;
            }
            return maxValue;
        }

        // Method that returns the index of the max element in the list.
        // Complexity: O(n)
        int maxIndex(){
            T maxValue = this->max();
            Node<T>* aux = head;
            int index = 0;
            
            while(aux != NULL){
                if(aux->data == maxValue){
                    break;
                }
                index++;
                aux = aux->next;
                
            }
            return index;
        }

        // Method that returns the min element in the list.
        // Complexity: O(n)
        T min(){
            T minValue = head->data;
            Node<T>* aux = head->next;

            while(aux != NULL){
                if(aux->data < minValue){
                    minValue = aux->data;
                }
                aux = aux->next;
            }
            return minValue;
        }

        // Method that returns the index of the max element in the list.
        // Complexity: O(n)
        int minIndex(){
            T minValue = this->min();
            Node<T>* aux = head;
            int index = 0;
            
            while(aux != NULL){
                if(aux->data == minValue){
                    break;
                }
                index++;
                aux = aux->next;
                
            }
            return index;
        }

        // Method that shows if the list is empty or not.
        // Complexity: O(1)
        bool isEmpty(){
            return head == NULL;
        }

    private:
        // Method that sorts the elements of the list using Merge Sort algorithm.
        // Complexity: O(n log(n))
        pair<Node<T>*, Node<T>* > mergeSort(int left, int right){
            if(left != right){
                // Find the half index.
                int middle = (right + left) / 2;

                // Instantiate Left and Right Sublists
                DoublyLinkedList<T>* leftList = new DoublyLinkedList();
                DoublyLinkedList<T>* rightList = new DoublyLinkedList();
                

                // Instantiate an Auxiliare node to travers thorugh the lists.
                Node<T>* aux = head;

                // Divide the list into to sublists and sort them.
                for(int i = 0; i <= middle; i++){
                    leftList->addLast(aux->data);
                    aux = aux->next;
                }

                for(int i = middle + 1; i <= right; i++){
                    rightList->addLast(aux->data);
                    aux = aux->next;
                }

                // Merge the sublists into a new one.
                DoublyLinkedList<T>* mergedList = new DoublyLinkedList();
                pair<Node<T>*, Node<T>* > leftPair = leftList->mergeSort(0, leftList->size - 1);
                pair<Node<T>*, Node<T>* > rightPair = rightList->mergeSort(0, rightList->size - 1);

                leftList->head = leftPair.first;
                leftList->tail = leftPair.second;
                
                rightList->head = rightPair.first;
                rightList->tail = rightPair.second;

                Node<T>* auxLeft = leftList->head;
                Node<T>* auxRight = rightList->head;

                // Add to mergeList the missing values.
                while(auxLeft != NULL && auxRight != NULL){
                    if(auxLeft->data < auxRight->data){
                        mergedList->addLast(auxLeft->data);
                        auxLeft = auxLeft->next;
                    }else{
                        mergedList->addLast(auxRight->data);
                        auxRight = auxRight->next;
                    }
                }

                if(auxLeft == NULL){
                    while(auxRight != NULL){
                        mergedList->addLast(auxRight->data);
                        auxRight = auxRight->next;
                    }
                }else if(auxRight == NULL){
                    while(auxLeft != NULL){
                        mergedList->addLast(auxLeft->data);
                        auxLeft = auxLeft->next;
                    }
                }

                pair<Node<T>*, Node<T>*> mergedPair;
                mergedPair.first = mergedList->head;
                mergedPair.second = mergedList->tail;

                return mergedPair;

            }else{
                pair<Node<T>*, Node<T>*> mergedPair;
                mergedPair.first = head;
                mergedPair.second = tail;
                return mergedPair;
            }
        }
};

#endif