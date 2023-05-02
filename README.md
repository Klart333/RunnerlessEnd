# RunnerlessEnd
 
An endless runner made in unreal engine. 

# Development

Let me start off with apoligizing for missing the first part submission, there was a 9-day long game jam I was giving my complete attention to, as it was fun and encouraged by the school. 
After that I have made the game, and missed the part of documenting bugs as I go along. ops. 

I guess I can just try to talk a bit about development here and hope for the best :)
Working in unreal as a beginner has been quite painful as everything is incredibly rigid, among other reasons.
The most recent example of this is that I was spawning obstacles with the ObstacleSpawner I made, makes sense. Aight but I want the obstacles to give a callback when they cross 0 as that's when the player dodges them etc. Could do it with an event but it seems a bit exaggerated to use a event for just that and also making an event takes like 8 words and I have to google it. So I just keep a reference to the ObstacleSpawner and call the function, right? Nope! That's a circular dependancy. Did I think of this? No. Did rider tell me anywhere, also no. Instead the TArray I made didn't have the Add function. Why of course, the common NoAddFunctionCausedByCircularDependancy exception, so that was very frustrating to debug. 

On multiple occasions I have wanted to setup an event in c++ that the UI can subscribe to and update accordingly. Sounds great, so I use the "ImplementableBlueprintEvent" or whatever. Nope. That's only for children. How did I solve this do you ask? Did I put the event in UObject so the widget has access to it, that sounds insane to me so; the ui just updates every frame. woo


I don't think I've actually talked about overcoming any challenges, just complained a lot. I can say for the first thing I have learned to try to compile when I have weird errors and read that instead. 

Oh, here's a challenge: When I tried to call the jump on the characters, they refuse to jump. It's the same function as when they were taking inputs themselves, just didn't do anything this time. Less of a function more of a malfunction I'd say. Well how did I solve this? My solution was to give up as you can play without jumping :)

That's probably pretty confusing without any background, why wouldn't the players be taking input themselves? Well, we needed two characters right, and I first thought that I would learn to properly use the new Enhanced input system for this. So I make the actions and the mapping contexts and setup it up. Alright only one player is taking input, makes sense as only one pawn can get possess by player 0 (for some reason). Google time, they say if I spawn in the character and the Player Controller and assign it then it'll work... 6 years ago, newer comments were saying it didn't work. As would I. I tried for multiple hours trying to understand why it didn't work, the characters were possessed by controllers but the spawned controller didn't seem to care about anything. Not sure but safe to say it didn't work and there were no other recommended approach as two characters on the same keyboard is a pretty niche problem. So I made a PlayerSpawner that took the input for both, spawned them in, and assigned input. Worked pretty well except for the fact that they refuse to jump. I think it has something to do with them not taking input so unreal just returns out of the default jump funtion. I did go and look but it was like a 400 line mess so ya know. 

I should put like a <b>10 min read</b> at the top of this, I feel kinda bad. Don't really think any of this is that useful for the grading. hmm, well, here's to hoping :)