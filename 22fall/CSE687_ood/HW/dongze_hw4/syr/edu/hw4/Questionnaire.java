package syr.edu.hw4;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;


public class Questionnaire {
    List<String> questions;
    public Questionnaire() {
        questions = new ArrayList<>();
    }
    public void addQuestion(String s) {
        questions.add(s);
    }
    public List<String> administerQuestionnaire() {
        List<String> answers = new ArrayList<>();
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        for (String s: questions) {
            String response = "";
            if(s.charAt(s.length()-1) == '?') {//normal question
                System.out.println("True or False: ");
                System.out.println(s);

                loopA:
                while (true) {
                    try {
                        response = reader.readLine();
                        if (response.equals("True") || response.equals("False"))
                            break loopA;
                        else
                            throw new IOException("Invalid response! Please only enter True/False!");
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    System.out.println("True or False: ");
                    System.out.println(s);
                }
            }
            else{//likert scale question
                System.out.println("Please response with an integer in the range 1-5:");
                System.out.println("1 means Strong Disagree");
                System.out.println("2 means Somewhat Disagree");
                System.out.println("3 means Neutral");
                System.out.println("4 means Somewhat Agree");
                System.out.println("5 means Strongly Agree");
                System.out.println(s);

                loopB:
                while (true) {
                    try {
                        response = reader.readLine();
                        if (response.equals("1") || response.equals("2") || response.equals("3")
                        ||response.equals("4") || response.equals("5"))
                            break loopB;
                        else
                            throw new IOException("Invalid response! Please only enter integer from 1 to 5");
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    System.out.println("Please response with an integer in the range 1-5:");
                    System.out.println("1 means Strong Disagree");
                    System.out.println("2 means Somewhat Disagree");
                    System.out.println("3 means Neutral");
                    System.out.println("4 means Somewhat Agree");
                    System.out.println("5 means Strongly Agree");
                    System.out.println(s);
                }
            }
            answers.add(response);
        }
        return answers;
    }

    public static void main(String[] args) {
        Questionnaire q = new Questionnaire();
        q.addQuestion("Are you awake?");
        q.addQuestion("Have you had coffee?");
        q.addQuestion("Are you ready to get to work?");
        q.addQuestion("CSE 687 is awesome.");
        List<String> answers = q.administerQuestionnaire();
        System.out.println("complete!");
        System.out.println(answers);
    }
}

