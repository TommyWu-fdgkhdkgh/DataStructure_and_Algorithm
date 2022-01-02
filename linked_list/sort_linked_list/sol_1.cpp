// 普通的 merge sort

// 看了 https://labuladong.gitbook.io/algo/di-ling-zhang-bi-du-xi-lie/hua-dong-chuang-kou-ji-qiao-jin-jie
//   讓我回憶起了還有快慢指針可以使用

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// merge sort

class Solution {
public:
    
    ListNode* mergesort(ListNode *lefthead, ListNode *righthead) {
        
        //cout << "lefthead->val : " << lefthead->val << ", righthead->val : " << righthead->val << endl;
        
        if(lefthead == NULL || righthead == NULL) {
            if(lefthead != NULL) {
                return lefthead;
            } else if(righthead != NULL) {
                return righthead;
            }
        }
        
        if(lefthead == righthead){
            return lefthead;
        }
        
        //lefthead
        ListNode* llhead;
        ListNode* lrhead;
        ListNode* lend;
        
        //righthead
        ListNode* rlhead;
        ListNode* rrhead;
        ListNode* rend;
        
        ListNode* slowp;
        ListNode* fastp;
        
        
        slowp = lefthead;
        fastp = lefthead;
        while(fastp->next != righthead) {
            //cout << "gg 1" << endl;
            
            slowp = slowp->next;
            
            fastp = fastp->next;
            if(fastp->next == righthead) {
                break;
            } else {
                fastp = fastp->next;
            }
        }
        
        llhead = lefthead;
        lrhead = slowp;
        fastp->next = NULL;
        
        slowp = righthead;
        fastp = righthead;
        while(fastp->next != NULL) {
            //cout << "gg 2" << endl;
            
            slowp = slowp->next;
            
            fastp = fastp->next;
            if(fastp->next == NULL) {
                break;
            } else {
                fastp = fastp->next;
            }
        }
        
        rlhead = righthead;
        rrhead = slowp;
        fastp->next = NULL;
        
        lefthead = mergesort(llhead, lrhead);
        righthead = mergesort(rlhead, rrhead);
        return merge(lefthead, righthead);
        //return NULL;
        
    }
    
    // lefthead 跟 righthead 是兩個已排序好的 linked list
    //   將兩個已排序好的 linked list 排序在一起
    ListNode* merge(ListNode* lefthead, ListNode* righthead) {
        
        //cout << "merge stage --- lefthead->val : " << lefthead->val << ", righthead->val : " << righthead->val << endl;
        
        ListNode* mergehead = NULL;
        ListNode* mergep = NULL;
        
        while(lefthead != NULL && righthead != NULL) {
            //cout << "gg 3" << endl;
            
            if(lefthead->val < righthead->val) {
                if(mergehead == NULL) {
                    mergehead = lefthead;
                    mergep = mergehead;
                    lefthead = lefthead->next;
                } else {
                    mergep->next = lefthead;
                    mergep = mergep->next;
                    lefthead = lefthead->next;
                }
            } else {
                if(mergehead == NULL) {
                    mergehead = righthead;
                    mergep = mergehead;
                    righthead = righthead->next;
                } else {
                    mergep->next = righthead;
                    mergep = mergep->next;
                    righthead = righthead->next;
                }
            }
        }
        
        if(lefthead == NULL) {
            mergep->next = righthead;
        } else if(righthead == NULL) {
            mergep->next = lefthead;
        } else {
            cout << "ERROR!" << endl;
        }
        
        //cout << "mergehead : ";
        /*for(ListNode* i = mergehead;i != NULL;i = i->next) {
            cout << " " << i->val << " ";
        }
        cout << endl;
        */
        
        return mergehead;
    }
    
    ListNode* sortList(ListNode* head) {
        int len = 0;
                
        ListNode* slowp = head;
        ListNode* fastp = head;
        
        ListNode* lefthead;
        ListNode* righthead;
        
        while(fastp != NULL) {
            //slow pointer
            slowp = slowp->next;
            
            //fast pointer
            fastp = fastp->next;
            if(fastp == NULL) {
                break;
            } else {
                fastp = fastp->next;   
            }
        }
        
        lefthead = head;
        righthead = slowp;
        
        //cout << "lefthead->val : " << lefthead->val << endl;
        //cout << "righthead->val : " << righthead->val << endl;

        lefthead = mergesort(lefthead, righthead);
        
        return lefthead;
    }
};
