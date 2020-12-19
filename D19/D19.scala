import scala.io.Source
import scala.collection.mutable.ListBuffer

object D19 {
    def main(args: Array[String]) = {
        val RULE_COUNT = 133

        var regexs = Array.ofDim[String](RULE_COUNT)
        var stmts = ListBuffer[String]()
        var isMapped = Array.ofDim[Boolean](RULE_COUNT)
        var isMappedCnt: Int = 0
        var lineBreak: Int = 0
        for(line <- Source.fromFile("input.txt").getLines()) {
            if(line == "") {
                lineBreak += 1
            } else {
                if(lineBreak == 0) {
                    val tokens = line.split(": ")
                    val idx = tokens(0).toInt
                    regexs(idx) = "( " + tokens(1).replace("\"", "") + " )"
                    
                    if(regexs(idx).matches("[ab]")) {
                    // part 2
                    // if(regexs(idx).matches("[ab]") || idx == 0 || idx == 8 || idx == 11) {
                        isMapped(idx) = true
                        isMappedCnt += 1
                    }
                } else {
                    stmts += line
                }
            }
        }

        while(isMappedCnt < RULE_COUNT) {
            for(i <- 0 to (RULE_COUNT - 1)) {
                if(!isMapped(i)) {
                    val tokens = regexs(i).replace(" |", "")
                        .replace("( ", "")
                        .replace(" )", "")
                        .split(" ")

                    var matchCnt: Int = 0
                    for(token <- tokens) {
                        if(token.matches("[0-9]*") && isMapped(token.toInt)) {
                            matchCnt += 1
                        }
                    }

                    if(matchCnt == tokens.length) {
                        for(token <- tokens) {
                            if(token.matches("[0-9]*") && isMapped(token.toInt)) {
                                regexs(i) = regexs(i).replace(" " + token + " ", " " + regexs(token.toInt) + " ")
                            }
                        }
                    }

                    if(regexs(i).matches("[ab|() ]*")) {
                        regexs(i) = regexs(i).replace(" ", "")
                        isMapped(i) = true
                        isMappedCnt += 1
                    }
                }
            }
        }

        // part 2
        /*
        regexs(8) = regexs(8).replace(" " + "42" + " ", " " + regexs(42) + " ")
            .replace("8", "")
            .replace(" ", "") + "+"
        
        regexs(11) = "("
        for(i <- 1 to 40) {
            
            for(j <- 1 to i) {
                regexs(11) += regexs(42)
            }

            for(j <- 1 to i) {
                regexs(11) += regexs(31)
            }

            if(i != 40) {
                regexs(11) += "|"
            }

            println(i)
        }
        regexs(11) += ")"
        
        val regex = regexs(0).replace(" " + "8" + " ", " " + regexs(8) + " ")
            .replace(" " + "11" + " ", " " + regexs(11) + " ")
            .replace(" ", "")
        */

        val regex = regexs(0).replace(" ", "")

        var cnt: Int = 0
        for(stmt <- stmts) {
            if(stmt.matches(regex)) {
                cnt += 1
            }
        }

        println(cnt)
    }
}