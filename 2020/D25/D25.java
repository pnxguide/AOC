public class D25 {
    public static void main(String[] args) {
        final long CARD_PK = 3418282;
        final long DOOR_PK = 8719412;
        final long MOD = 20201227;
        long subjectNumber = 7;
        
        long value = 1;
        long cardLoopSize = 0;
        long doorLoopSize = 0;
        for(int i = 1; cardLoopSize == 0 || doorLoopSize == 0; i++) {
            value = (value * subjectNumber) % MOD;
            if(value == CARD_PK) {
                cardLoopSize = i;
            } else if(value == DOOR_PK) {
                doorLoopSize = i;
            }
        }

        long encryptionKey = 1;
        if(cardLoopSize < doorLoopSize) {
            subjectNumber = DOOR_PK;
            for(int i = 0; i < cardLoopSize; i++) {
                encryptionKey = (encryptionKey * subjectNumber) % MOD;
            }
        } else {
            subjectNumber = CARD_PK;
            for(int i = 0; i < doorLoopSize; i++) {
                encryptionKey = (encryptionKey * subjectNumber) % MOD;
            }
        }

        System.out.println(encryptionKey);
    }
}