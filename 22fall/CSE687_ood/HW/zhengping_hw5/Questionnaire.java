package syr.edu.hw5;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

class Question {
    private String q;
    private String prompt;
    private List<String> acceptableAnswers;
    public Question(String q, String prompt, List<String> acceptable) {
        this.q = q;
        this.prompt = prompt;
        acceptableAnswers = acceptable;
    }
    public void render(PrintStream p) {
        p.println(q);
        p.println(prompt);
    }
    public boolean isAcceptableAnswer(String s) {
        return acceptableAnswers.contains(s);
    }

    public String getPrompt(){
        return this.prompt;
    }
}
public class Questionnaire {
    List<Question> questions;
    public Questionnaire() {
        questions = new ArrayList<>();
    }
    public void addQuestion(Question q) {
        questions.add(q);
    }
    public List<String> administerQuestionnaire() {
        List<String> answers = new ArrayList<>();
        Scanner sc = new Scanner(System.in);
        for (Question q: questions) {
            q.render(System.out);
            String response = "";
            if(q.getPrompt() == "It's number 1-5: ") {
                int responseNumber = 0;
                do {
                    while(!sc.hasNext()) {
                        System.out.println("The input should from 1 to 5!");
                        sc.next();
                    }
                    responseNumber = sc.nextInt();
                } while (!q.isAcceptableAnswer(Integer.toString(responseNumber)));
                switch (responseNumber) {
                    case 1:
                        response = "Super Disagree";
                        break;
                    case 2:
                        response = "Disagree";
                        break;
                    case 3:
                        response = "I don't care";
                        break;
                    case 4:
                        response = "Agree";
                        break;
                    case 5:
                        response = "Super Agree";
                        break;
                }
            }else{
                do {
                    response = sc.nextLine();
                } while (!q.isAcceptableAnswer(response));
            }
            answers.add(response);
        }
        return answers;
    }

    public static void main(String[] args) {
        Questionnaire q = new Questionnaire();
        q.addQuestion(new Question("CSE 687 is awesome.", "It's number 1-5: ", Arrays.asList("1", "2", "3", "4", "5")));
        q.addQuestion(new Question("Are you awake?", "", Arrays.asList("True", "False", "true", "false", "t", "f", "T", "F")));
        q.addQuestion(new Question("Have you had coffee?", "True or False: ", Arrays.asList("True", "False", "true", "false", "t", "f", "T", "F")));
        q.addQuestion(new Question("Are you ready to get to work?", "True or False: ", Arrays.asList("True", "False", "true", "false", "t", "f", "T", "F")));
        List<String> answers = q.administerQuestionnaire();
        System.out.println("complete!");
        System.out.println(answers);
    }
}
