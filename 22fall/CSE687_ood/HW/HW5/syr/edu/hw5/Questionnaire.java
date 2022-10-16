package syr.edu.hw5;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

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

    public String getPrompt() {
        return prompt;
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
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        for (Question q : questions) {
            q.render(System.out);
            String response = "";
            do {
                try {
                    response = reader.readLine();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            } while (!q.isAcceptableAnswer(response));

            if (!q.getPrompt().equals("True or False: ")) {
                int response_id = Integer.parseInt(response);

                if (response_id == 1) {
                    response = "Strongly Agree";
                } else if (response_id == 2) {
                    response = "Somewhat Agree";
                } else if (response_id == 3) {
                    response = "Neutral";
                } else if (response_id == 4) {
                    response = "Somewhat Disagree";
                } else {
                    response = "Strong Disagree";
                }
            }

            answers.add(response);
        }
        return answers;
    }

    public static void main(String[] args) {
        Questionnaire q = new Questionnaire();
        q.addQuestion(new Question("Are you awake?", "True or False: ",
                Arrays.asList("True", "False", "true", "false", "t", "f", "T", "F")));
        q.addQuestion(new Question("Have you had coffee?", "True or False: ",
                Arrays.asList("True", "False", "true", "false", "t", "f", "T", "F")));
        q.addQuestion(new Question("Are you ready to get to work?", "True or False: ",
                Arrays.asList("True", "False", "true", "false", "t", "f", "T", "F")));
        q.addQuestion(new Question("CSE 687 is awesome.",
                "1(Strongly Agree), 2(Somewhat Agree), 3(Neutral), 4(Somewhat Disagree), 5(Strong Disagree): ",
                Arrays.asList("1", "2", "3", "4", "5")));
        List<String> answers = q.administerQuestionnaire();
        System.out.println("complete!");
        System.out.println(answers);
    }
}

// 0 VINs found

// View Showroom
// 0 VINs identified

// Send Feedback