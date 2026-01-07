## Leetcode Seminar

### Big Mistakes
1. Giving up too early
	- practice how to deal with struggles while solving problems, thinking about things from multiple perspectives
2. Using hints, AI or friends
3. Not doing the correct distribution
	- important to gain a broad understanding of concepts
4. Not studying the editorial/solution enough
	- think about why and how they came up with that solution and why it differs from your solution
5. Targeting specific concepts
	- deliberately choosing leetcodes that target certain concepts primes you on the solution.
	- this is not reflective of a real interview situation and should be avoided.
	- knowing the topic beforehand is a massive hint
	- even if you are weak in a certain concept, leetcodes should always be selected **randomly**.
6. Spamming the submission button and making quick fixes
	- In a real interview, if you make a mistake, you need to analyse your entire solution to look for structural issues. 
	- If you only check things one mistake at a time, you will likely end up missing a lot and seem very unreliable to the recruiter. 
	- Being jumpy to fix issues is the reason that production incidents occur 99% of the time in the industry.

### Leetcoding Process
1. Start by choosing a random problem with the specific difficulty you want to do. 
	- Do not target specific concepts, as it will prime you on the solution, and remove the realism associated with completing the Leetcode.
2. Gather some materials. 
	- Pen, paper and your language documentation are three things you’ll have access to in an interview, so you should get used to using them now.
3. Begin your stopwatch. You can use Leetcode, Google, Windows or your phone. This will be your reference for how long the problem took.
4. Complete the problem. 
	1. Read the question thoroughly and ensure you understand what it is asking before proceeding. I recommend not creating test cases to help you understand the problem, as this is not what you will have access to in the interview.
	2. If you are stuck on an approach, pseudocode it out. Try to use comments as much as possible to document your ideas, breaking it down into steps and pseudocoding as much as possible. Write down as much as you know, even if you think it is dumb, because you want to reinforce it in your head.
	3. Once you have a complete algorithm, start coding. If you can’t get an algorithm after 1 hour, I would also consider coding, but not any time before that. It is often ill-advised to begin coding if you don’t know where you’re headed. Code from start to finish, paying close attention to your code quality.
	4. Once your code is complete, I recommend engineering some edge cases you think will be good. This will help you practise thinking of edge cases in mock interviews and real interviews as well.
	5. Run the code against your sample cases. If it fails, then retry, debugging using print statements where necessary to represent the intermediate state.
	6. Once all of your sample cases are passing and you feel confident about your code, then you should submit. 
		- If it fails on WA, add the case to your set, and retry the process above.
		- If it fails on TLE/MLE, your solution does not have the correct time or space complexity, and has serious architectural issues. You will need a strong optimisation, this may involve starting again.

### Studying the Solution
Even if you are able to solve the problem correctly, you should study the solution. 
- There will often be a solution with a better complexity, cleaner code, or one that uses standard library tricks to make your life easier. 
- If you can, start by reading through the Leetcode official solutions. 
	- Take your time to study each one, understanding why it is correct, how it works, as well as its complexities and any standard library functions used. 
	- You should be able to recreate every solution you study from scratch without needing your notes; hopefully this puts into perspective how well you need to be studying. 
	- If you skim over the solutions without understanding them, then you have not really done a Leetcode but instead have wasted your time.
- If no official solution or paywalled, look at community solutions (`lee215` is a good contributor)
- Generally, you should spend at least 1 hour studying the solution and re-implementing the answer, with extra long time dedicated to those with particularly tricky solutions. The longest time Ravi ever spent on a problem was 2 days.
- Neetcode is the best teacher
- For a Leetcode problem, probably 2 hours at most. Usually 1 hour, ~25-30min of solving and the 30 min of studying and reflection/analysis

*Can confirm Atlassian asks easies. Easies also show up in OAs. Mediums usually show up in technical rounds in quant and big tech. I’ve only ever gotten hards in the citadel OA, and I’ve heard of hards getting asked at Google and Tiktok. The time bounds for each are realistic for interviews*

---
## Mock Interview Seminar
Each mock interview goes for 45 minutes, and is composed of three parts:
- 1-2 Behavioural Questions.
	- Taking 5 minutes.
- 1 Easy Leetcode
	- Taking 10 minutes.
- 1 Medium Leetcode
	- Taking 25 minutes.

Regarding the time limit:
- Interviews can be very short for the amount of content you need to get through. 
- RSP interviews teach you how to be efficient during your interview, as time is very valuable
- In big tech and HFT interviews you would be expected to complete 1 behavioural and 1 medium Leetcode in that same amount of time (45 mins)

### Introductions
- Include in your response 
	- University, degree & year 
	- Why you like comp sci/got into it (optional) 
	- Relevant work experience 
	- A bit about one of your interesting projects (why you did it, what you learnt) 
	- Relevant community involvement 
- Some interviewers also like to hear about your hobbies and interests outside of comp sci. I don’t think this is very important but I think it can be a good idea to spend 15 seconds on this at the end of your response. It might make you seem more human and relate to your interviewer.
- This should take about ~2 minutes 
- Have an idea of the points you want to hit and the order, but don’t follow an exact script

### Behavioural
#### Questions
- There are usually 2 types of behaviourals with the recruiter. Either they will look at your resume and tailor their questions to it. 
- Alternatively, they will try to standardize the interview by asking the same common questions to everyone.
- For RSP mocks, I find it helpful to ask questions based on the former
	- ask interviewee for resume
- On language: you should not use hypotheticals starting with “you” but use “I” to sound like you take personal responsibility. “You” sounds like a hypothetical. “I” is concrete.
	- Also, when using “we”, make sure to clarify who “we” is. Who was part of your team?

#### Responses
 STARR (situation, task, action, result, reflection) is a solid format. 
- Don't explicitly saying these i.e. don’t say “the situation was”, but keep this in mind
- You should be hitting each of these points with your response and using STARR to structure your answers. 
- Once you get a lot of practice you may develop your own format, but it will likely still be similar to STARR
- You will encounter questions you can’t answer with STARR, for these you should still be thinking consciously about format before you give your answer. 
- You should give people questions they can’t just use STARR to answer. 
- Examples: 
	- Think of a piece of software you use on a daily basis related to software development. How would you explain this to your grandma? 
	- What are your 3 biggest weaknesses?

### Technical
#### Interviewer
- Questions should be leetcodes that you have completed and the interviewee has not
	- check RSP and leetcode profiles
- Try to select questions:
	- That you are confident in the answer to.
	- That is well-rated (the easy is easy, and the medium is medium).
	- That has a sufficient amount of complexity, often with multiple answers (although some good questions only have one approach).
	- That stays within the realm of standard DSA, and doesn't require esoteric knowledge or observations that you consider hard.
	- That you would be happy to see in an interview.
- Try to avoid giving the same question more than twice, because by then you will have learnt all you can from it.
	- You also learn from seeing other people attempt the question
- Sometimes it can be good to give a question you don't expect people will pass - it’s better to do poorly in a mock than a real interview. Knowing how to handle being completely stuck is also important.
	- if you are really stuck, you can tell the interviewer all the approaches you have thought of and why they won’t work, and ask them for feedback.
	- but make sure you’ve thought hard about all possible approaches first!

#### Interviewee
**Confirming the question**
- ensure you understand what the interviewer is asking for, and extract as much information as possible
- five key components:
	1. Clarify ambiguities: ensure high-level understanding of the question is correct by asking clarifying questions
	2. Repeat the question: describe what is being asked for in your own words, in different terms that allow you to capture complexities
	3. Input sizes: ask about length of a list, size of a graph, number of neighbours for each node, dimensions of a grid, etc. Most crucial.
	4. Input values: range of values in a list, letters allowed in a string, etc.
		- If a question only works with a small range of values, caching all the answers could be feasible
	5. Input and output: come up with an example input/output pair for the question, at least one standard case and one edge case. Confirm correctness
- *If the interviewee continues past this phase, but later realises that they haven’t clarified a part of the question, they should lose marks. If it’s a key part that relates to the solution of a question, they should fail this section.*

**Algorithm Design**
- Come up with a brute-force solution first, and explain why it is necessary or doesn't work (with relation to complexity)
	- Some problems will *only* have a brute-force solution
- Then describe optimal solution. Three important aspects:
	1. The speed to come up with optimal algorithm
	2. The correctness of the algorithm within time/space constraints
	3. The clarity in which they write and describe the algorithm
- If you feel the need to go silent to think for a long period of time, you should ask permission from your interviewer. However, try to keep these as short as possible.
- *If the interviewee comes up with the optimal solution, you should not fail them.*
	- *Dock points for slowness or lack of clarity*
	- *Google cares about clarity a lot*

**Complexity Analysis**
- Need to do better than stating the time/space complexity
- Step through pseudocode algorithm and explain time and space taken by each step
- Need to become comfortable describing the complexity of tricky algorithms
	- can do by reciting the complexity after every Leetcode problem you do, then checking your answer and explanation against the editorial.
- *If the interviewee knows that the complexity of their algorithm is, but can’t explain it, then they should barely pass with a 5.* 
	- *More in-depth explanations should get increasing points, with a perfectly comprehensive, but not wordy, explanation scoring 10.*

**Coding**
- Don't start coding until you have designed an algorithm (unless you are very confident)
- Turn pseudocode into comments and use as structural guide
- Explain what you are writing as you go
	- Explain both logically and syntactically (what features or stdlib functions you are using)
- Brief pauses are okay but going silent for long periods in an interview is bad
- *If the interviewee completes their code correctly but doesn’t speak, you should fail them with a 4. At least a little communication is required for a passing grade. If the interviewee’s code is not reasonably correct by the time the interview has finished, they should also fail.*

**Testing**
- Won't have an IDE to run your code
	- Need to test manually on paper
- Use one of your sample cases from before and run through each step line by line
	- store intermediate states on paper
	- run algorithm to completion - choose a small but non-trivial test case
- If you find a bug:
	- explain to interviewer you found a bug
	- run through code again and patch the bug, all places it might exist, and any other issues
	- allow only one chance to fix issues
	- if after fixing your bug, your code still has bugs, interview will likely question your debugging skills / how well you understand your algorithm. 
- *If the interviewee tests their code, but doesn’t make how the algorithm is working very clear, then they should fail.*
	- *The more they explain and record how their code is operating, the greater the score they should get. Be sure to allocate points for speed also.*

### Feedback
- Valuable to both give feedback about what parts went well and went poorly. First, emphasize what went well, then what could be improved.
- Take notes as both the interviewee *and* interviewer to keep track of feedback points
- Be harsh with your markings and give positive criticism - its better them hearing it now and addressing it then hearing it in a real interview 
- As the interviewee, if you disagree with your interviewer on feedback, discuss this. There is a reason each of you would have your own views on this, discuss it and find out why. Often you are both partially right.

### Extended Mocks
- As you are probably aware, behavioural and technical aren’t the only kinds of questions that can show up in interviews. Operating Systems, OOP and System Design are all very relevant, which can show up both as questionnaires and design interviews.
- To promote to Advanced in RSP, we require students to do at least two extended mocks, which can be any of the following, or more:
	- Pure Behavioural
	- Object Oriented Design
	- System Design
	- Custom technical questions (implement a heap etc)
	- SRE mocks - debugging and proposing future fixes to an imaginary system. Only applicable if going for SRE roles