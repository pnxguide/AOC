class CircularLinkedList {
    Node head;
    Node cur;
    Node[] index;
    int length;

    CircularLinkedList(int data) {
        head = new Node(data);
        cur = head;

        length = 1;

        index = new Node[1000001];
        index[data] = cur;
    }
    
    void add(int data) {
        cur.next = new Node(data);
        cur = cur.next;
        length++;

        index[data] = cur;
    }

    void printTwoAfter() {
        long n1 = index[1].next.data;
        long n2 = index[1].next.next.data;
        System.out.println(n1 * n2);
    }

    void printOrder() {
        Node q = index[1];
        while(q.next.data != 1) {
            System.out.print(q.next.data);
            q = q.next;
        }
        System.out.println();
    }

    Node find(int x) {
        return index[x];
    }
}

class Node {
    int data;
    Node next;

    Node(int data) {
        this.data = data;
        this.next = null;
    }

    Node(int data, Node next) {
        this.data = data;
        this.next = next;
    }
}

public class D23 {
    public static void main(String[] args) {
        char[] inputs = "18946572".toCharArray();
        CircularLinkedList list = new CircularLinkedList(3);
        for(char input : inputs) {
            list.add(Character.getNumericValue(input));
        }

        for(int i = 10; i <= 1000000; i++) {
            list.add(i);
        }

        list.cur.next = list.head;

        Node cur = list.head;
        for(int i = 0; i < 10000000; i++) {
            Node[] picks = new Node[]{cur.next, cur.next.next, cur.next.next.next};
            int desNum = cur.data;

            boolean isDesValid = true;
            do {
                isDesValid = true;
                desNum = ((desNum + 999998) % 1000000) + 1;
                for(Node j : picks) {
                    if(j.data == desNum) {
                        isDesValid = false;
                        break;
                    }
                }
            } while(!isDesValid);

            Node des = list.find(desNum);
            cur.next = picks[2].next;
            picks[2].next = des.next;
            des.next = picks[0];
        
            cur = cur.next;
        }

        list.printTwoAfter();
    }
}
