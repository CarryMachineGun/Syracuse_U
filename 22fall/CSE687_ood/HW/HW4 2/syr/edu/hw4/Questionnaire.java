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
        for (String s : questions) {
            String response = "";

            if (s.charAt(s.length() - 1) == '?') {
                System.out.println("True or False: ");
                System.out.println(s);

                while (true) {
                    try {
                        response = reader.readLine();
                        if (response.equals("True") || response.equals("False"))
                            break;
                        else {
                            System.out.println("Invalid response!");
                            // throw new IOException("Invalid response!");
                        }
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            } else {
                System.out.println(
                        "1(Strongly Agree), 2(Somewhat Agree), 3(Neutral), 4(Somewhat Disagree), 5(Strong Disagree): ");
                System.out.println(s);

                while (true) {
                    try {
                        response = reader.readLine();
                        if (response.length() == 1 && response.charAt(0) >= '1' && response.charAt(0) <= '5') {
                            if (response.charAt(0) == '1')
                                response = "1(Strongly Agree)";
                            else if (response.charAt(0) == '2')
                                response = "2(Somewhat Agree)";
                            else if (response.charAt(0) == '3')
                                response = "3(Neutral)";
                            else if (response.charAt(0) == '4')
                                response = "4(Somewhat Disagree)";
                            else
                                response = "5(Strong Disagree)";
                            break;
                        } else {
                            System.out.println("Invalid response!");
                            // throw new IOException("Invalid response!");
                        }
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
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
