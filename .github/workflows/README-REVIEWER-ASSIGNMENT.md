# GitHub Actions: Auto-Assign PR Reviewers - Complete Guide

## 📖 Overview

This guide demonstrates how to automatically assign reviewers to pull requests based on their target branch. You now have **four different approaches** to choose from!

## 🎯 Available Implementations

### 1. **Basic Shell Script** (`auto-request-reviewers.yml`)
- ✅ Simple and straightforward
- ✅ No dependencies
- ✅ Easy to understand
- ❌ Limited logic capabilities
- **Use when:** You have simple branch patterns and static reviewer lists

### 2. **Simplified Version** (`auto-request-reviewers-example.yml`)
- ✅ Cleaner, easier to read
- ✅ Good for small teams
- ✅ Easy to modify
- **Use when:** You're just getting started or have a simple setup

### 3. **Config File Based** (`auto-request-reviewers-advanced1.yml`)
- ✅ Reviewers defined in separate JSON file
- ✅ Non-developers can update reviewers
- ✅ Cleaner separation of config and logic
- ❌ Requires checking out repository
- **Use when:** You want non-technical people to manage reviewers

### 4. **JavaScript Based** (`auto-request-reviewers-advanced2.yml`)
- ✅ Most flexible and powerful
- ✅ Can implement complex logic
- ✅ Automatically filters out PR author
- ✅ Better error handling
- ❌ Slightly more complex
- **Use when:** You need advanced logic or conditional assignment

## 🔧 How to Implement

### Step 1: Choose Your Approach
Pick one of the four files above based on your needs.

### Step 2: Create the Workflow File
```bash
# Create workflows directory if it doesn't exist
mkdir -p .github/workflows

# Copy your chosen approach
cp auto-request-reviewers.yml .github/workflows/
```

### Step 3: Customize the Branch Mapping
Edit the file and update these sections:

**For Shell Scripts (approaches 1 & 2):**
```bash
case "$TARGET_BRANCH" in
  main)
    REVIEWERS="your-reviewer1,your-reviewer2"
    ;;
  release/*)
    REVIEWERS="release-manager"
    ;;
  *)
    REVIEWERS=""
    ;;
esac
```

**For Config-Based (approach 3):**
Create `.github/REVIEWERS.json`:
```json
{
  "main": ["user1", "user2"],
  "release/*": ["releaseuser"],
  "develop": ["devuser1", "devuser2"]
}
```

**For JavaScript (approach 4):**
```javascript
const branchConfig = {
  'main': {
    reviewers: ['your-user1', 'your-user2'],
    teams: [] // or ['your-team-name']
  },
  // Add more branches...
};
```

### Step 4: Update Usernames
Replace placeholder usernames with actual GitHub usernames from your organization.

### Step 5: Test
1. Commit and push the workflow file
2. Create a test PR targeting one of your configured branches
3. Check if reviewers are automatically assigned

## 🎓 Key Concepts Explained

### Trigger Events
```yaml
on:
  pull_request:
    types: [opened, reopened, ready_for_review]
```

- **opened**: New PR created
- **reopened**: Closed PR reopened  
- **ready_for_review**: Draft PR marked as ready
- **synchronize**: New commits pushed (usually NOT needed for reviewer assignment)

### Branch Pattern Matching

| Pattern | Matches | Example |
|---------|---------|---------|
| `main` | Exact match | Only `main` |
| `release/*` | Wildcard | `release/1.0`, `release/v2.3` |
| `feature/*` | Wildcard | `feature/new-api`, `feature/bugfix` |
| `*` | Any branch | Fallback for all others |

### Permissions
```yaml
permissions:
  pull-requests: write  # Required to add reviewers
  contents: read        # Standard read access
```
Always use minimum required permissions for security.

### GitHub Contexts
- `github.event.pull_request.base.ref` - Target branch (where PR will merge)
- `github.event.pull_request.head.ref` - Source branch (where PR comes from)
- `github.event.pull_request.number` - PR number
- `github.event.pull_request.user.login` - PR author

## 🛠️ Common Customizations

### Exclude Certain Authors
```yaml
if: |
  !github.event.pull_request.draft &&
  github.event.pull_request.user.login != 'dependabot[bot]'
```

### Multiple Branch Patterns
```bash
case "$TARGET_BRANCH" in
  main|master|production)
    REVIEWERS="user1,user2"
    ;;
  release/*|hotfix/*)
    REVIEWERS="releaseuser"
    ;;
esac
```

### Team Reviewers
```bash
TEAM_REVIEWERS="org/team-name"  # Replace 'org' with your GitHub organization
```

### Different Reviewers Based on Files Changed
This requires checking out the repo and analyzing changed files:
```yaml
- uses: actions/checkout@v4
- name: Check changed files
  run: |
    if git diff --name-only ${{ github.event.pull_request.base.sha }} | grep "^docs/"; then
      REVIEWERS="docs-team-member"
    fi
```

## ⚠️ Common Pitfalls

### 1. Case Sensitivity
Branch names are case-sensitive. `Main` != `main`.

### 2. Comma Spacing
❌ Wrong: `"user1, user2, user3"` (spaces will cause errors)
✅ Correct: `"user1,user2,user3"`

### 3. Team Name Format
❌ Wrong: `"org/team-name"` in API call
✅ Correct: Extract just `"team-name"` for the API

### 4. PR Author Can't Review Own PR
The JavaScript version automatically filters this out.

### 5. Draft PRs
Always check `!github.event.pull_request.draft` to skip draft PRs.

## 🧪 Testing Your Workflow

### Test Locally (Parse Logic)
```bash
# Test your case statement
TARGET_BRANCH="release/1.5"
case "$TARGET_BRANCH" in
  release/*) echo "Match!" ;;
  *) echo "No match" ;;
esac
```

### Test in GitHub
1. Create a test branch
2. Open a PR from test branch → main (or your configured branch)
3. Check the "Actions" tab to see workflow execution
4. Verify reviewers were added to the PR

### Debug Mode
Add this to see more details:
```bash
set -x  # Enable debug output
echo "Debug: TARGET_BRANCH=$TARGET_BRANCH"
echo "Debug: REVIEWERS=$REVIEWERS"
```

## 📊 Comparison Matrix

| Feature | Basic Shell | Example | Config File | JavaScript |
|---------|------------|---------|-------------|------------|
| Easy to understand | ✅ | ✅✅ | ✅ | ❌ |
| No checkout needed | ✅ | ✅ | ❌ | ✅ |
| Non-dev friendly | ❌ | ❌ | ✅ | ❌ |
| Complex logic | ❌ | ❌ | ❌ | ✅ |
| Auto-filter author | ❌ | ❌ | ❌ | ✅ |
| Error handling | ⚠️ | ⚠️ | ⚠️ | ✅ |

## 🚀 Next Steps

1. **Choose your approach** based on your team's needs
2. **Customize the branch mapping** with your actual branches and reviewers
3. **Test with a dummy PR** before rolling out
4. **Document your process** so team members know how it works
5. **Monitor the Actions tab** to ensure it's working as expected

## 📚 Additional Resources

- [GitHub Actions Documentation](https://docs.github.com/en/actions)
- [Pull Request API](https://docs.github.com/en/rest/pulls/review-requests)
- [Workflow Syntax](https://docs.github.com/en/actions/using-workflows/workflow-syntax-for-github-actions)
- [GitHub CLI in Actions](https://docs.github.com/en/actions/using-workflows/using-github-cli-in-workflows)

## 💡 Pro Tips

1. **Start simple** - Use the example version first, then add complexity as needed
2. **Use team reviewers** for better load distribution
3. **Add comments** to your workflow file for future maintainers  
4. **Consider round-robin** assignment for fair distribution (requires more complex logic)
5. **Log everything** during testing to debug issues quickly

---

**Questions?** Check the GitHub Actions logs in your repository's "Actions" tab for detailed execution information!
