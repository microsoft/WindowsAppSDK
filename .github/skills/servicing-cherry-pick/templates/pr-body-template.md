## Cherry-Pick: #{{ORIGINAL_PR_NUMBER}} - {{ORIGINAL_PR_TITLE}}

| Field | Value |
|-------|-------|
| **Original PR** | [#{{ORIGINAL_PR_NUMBER}}](https://github.com/{{REPOSITORY}}/pull/{{ORIGINAL_PR_NUMBER}}) |
| **Target Branch** | `{{TARGET_BRANCH}}` |
| **Servicing Version** | {{VERSION_STRING}} |
| **ADO Bug** | {{BUG_ID}} |
| **Containment Enum** | `{{ENUM_NAME}}` |

### Changes

Cherry-pick of #{{ORIGINAL_PR_NUMBER}} to `{{TARGET_BRANCH}}` with servicing containment wrapping.

### Containment

All code changes are wrapped with `IsChangeEnabled<WINAPPSDK_CHANGEID_{{BUG_ID}}>()` for runtime rollback capability.

### Testing

- [ ] Cherry-pick applies cleanly
- [ ] Containment wrapping is correct
- [ ] IDL enum entry added
- [ ] Build succeeds
- [ ] Existing tests pass
